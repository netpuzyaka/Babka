#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#include <tchar.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <dxgi.h>
#include <dwmapi.h>
#include <algorithm>
#include <cstring>
#include <cstdint>

#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/imgui_impl_win32.h"
#include "../../lib/imgui/imgui_impl_dx11.h"
#include <gui.hpp>
#include <imgui_internal.h>
#include <dxgi1_2.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "dwmapi.lib")

using Microsoft::WRL::ComPtr;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

namespace {
    HMODULE gSelfModule{};

    HWND gGameWnd{}, gOverlayWnd{};
    ComPtr<ID3D11Device>           gDev;
    ComPtr<ID3D11DeviceContext>    gCtx;
    ComPtr<ID3D11Texture2D>        gRTTex;
    ComPtr<ID3D11RenderTargetView> gRTV;
    ComPtr<ID3D11Texture2D>        gStageTex;

    bool  gRun = true, gReady = false;
    bool  gMinimized = false;

    HDC     gMemDC{};
    HBITMAP gDIB{};
    void* gDIBBits{};
    int     gW{}, gH{};


    HWINEVENTHOOK gLocHook{};
    HWINEVENTHOOK gMoveHook{};
    volatile bool gIsMoving = false;

    void CopyRTtoDIB_Direct()
    {
        if (!gStageTex || !gDIBBits) return;
        gCtx->CopyResource(gStageTex.Get(), gRTTex.Get());
        D3D11_MAPPED_SUBRESOURCE map{};
        if (FAILED(gCtx->Map(gStageTex.Get(), 0, D3D11_MAP_READ, 0, &map))) return;

        const uint8_t* srcBase = static_cast<const uint8_t*>(map.pData);
        uint8_t* dstBase = static_cast<uint8_t*>(gDIBBits);
        const size_t dstStride = size_t(gW) * 4;

        for (int y = 0; y < gH; ++y) {
            const uint8_t* srow = srcBase + y * map.RowPitch;
            uint8_t* drow = dstBase + size_t(y) * dstStride;
            memcpy(drow, srow, dstStride);
        }
        gCtx->Unmap(gStageTex.Get(), 0);
    }

    void ULWPresent()
    {
        POINT ptSrc{ 0,0 };
        RECT wr{}; GetWindowRect(gOverlayWnd, &wr);
        POINT ptDst{ wr.left, wr.top };
        SIZE  size{ gW, gH };
        BLENDFUNCTION bf{};
        bf.BlendOp = AC_SRC_OVER;
        bf.SourceConstantAlpha = 255;
        bf.AlphaFormat = AC_SRC_ALPHA;
        UpdateLayeredWindow(gOverlayWnd, nullptr, &ptDst, &size, gMemDC, &ptSrc, 0, &bf, ULW_ALPHA);
    }

    void PrimeULW()
    {
        if (!gRTV || !gDIBBits) return;
        D3D11_VIEWPORT vp{};
        vp.TopLeftX = 0.0f; vp.TopLeftY = 0.0f;
        vp.Width = (float)gW; vp.Height = (float)gH;
        vp.MinDepth = 0.0f; vp.MaxDepth = 1.0f;
        gCtx->RSSetViewports(1, &vp);

        const float clear[4] = { 0,0,0,0 };
        gCtx->OMSetRenderTargets(1, gRTV.GetAddressOf(), nullptr);
        gCtx->ClearRenderTargetView(gRTV.Get(), clear);

        CopyRTtoDIB_Direct();
        ULWPresent();

        SetWindowPos(gOverlayWnd, gGameWnd, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW | SWP_ASYNCWINDOWPOS);
    }

    void DestroyDIB()
    {
        if (gMemDC) { DeleteDC(gMemDC); gMemDC = nullptr; }
        if (gDIB) { DeleteObject(gDIB); gDIB = nullptr; }
        gDIBBits = nullptr;
    }

    bool CreateDIB(int w, int h)
    {
        DestroyDIB();
        gMemDC = CreateCompatibleDC(nullptr);
        if (!gMemDC) return false;
        BITMAPINFO bi{};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = w;
        bi.bmiHeader.biHeight = -h;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;
        gDIB = CreateDIBSection(gMemDC, &bi, DIB_RGB_COLORS, &gDIBBits, nullptr, 0);
        if (!gDIB || !gDIBBits) return false;
        SelectObject(gMemDC, gDIB);
        gW = w; gH = h;
        return true;
    }

    void DestroyD3D()
    {
        gRTV.Reset();
        gStageTex.Reset();
        gRTTex.Reset();
        gCtx.Reset();
        gDev.Reset();
    }

    bool CreateD3D(int w, int h)
    {
        UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
        D3D_FEATURE_LEVEL req[] = { D3D_FEATURE_LEVEL_11_0};
        D3D_FEATURE_LEVEL got{};
        if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
            req, (UINT)(sizeof(req) / sizeof(req[0])), D3D11_SDK_VERSION,
            gDev.GetAddressOf(), &got, gCtx.GetAddressOf())))
            return false;

        D3D11_TEXTURE2D_DESC rt{};
        rt.Width = w; rt.Height = h;
        rt.MipLevels = 1; rt.ArraySize = 1;
        rt.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        rt.SampleDesc.Count = 1;
        rt.Usage = D3D11_USAGE_DEFAULT;
        rt.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        if (FAILED(gDev->CreateTexture2D(&rt, nullptr, gRTTex.GetAddressOf()))) return false;
        if (FAILED(gDev->CreateRenderTargetView(gRTTex.Get(), nullptr, gRTV.GetAddressOf()))) return false;

        D3D11_TEXTURE2D_DESC st = rt;
        st.Usage = D3D11_USAGE_STAGING;
        st.BindFlags = 0;
        st.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        if (FAILED(gDev->CreateTexture2D(&st, nullptr, gStageTex.GetAddressOf()))) return false;

        return true;
    }

    void ResizeAll(int w, int h)
    {
        DestroyD3D();
        CreateD3D(w, h);
        CreateDIB(w, h);
        PrimeULW();
    }

    bool FindGame()
    {
        gGameWnd = FindWindowA(nullptr, "Rust");
        if (!gGameWnd) gGameWnd = GetForegroundWindow();
        return gGameWnd != nullptr;
    }

    void SyncToGameWindowNow()
    {
        if (!gOverlayWnd || !gGameWnd || !IsWindow(gGameWnd)) return;
        RECT r{};
        GetWindowRect(gGameWnd, &r);
        int nx = r.left, ny = r.top, nw = r.right - r.left, nh = r.bottom - r.top;
        SetWindowPos(gOverlayWnd, gGameWnd, nx, ny, nw, nh,
            SWP_NOACTIVATE | SWP_SHOWWINDOW | SWP_ASYNCWINDOWPOS);
        RECT cr{}; GetClientRect(gOverlayWnd, &cr);
        int w = cr.right - cr.left, h = cr.bottom - cr.top;
        if (w != gW || h != gH) ResizeAll(w, h);
    }

    void CALLBACK LocEventProc(HWINEVENTHOOK, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD, DWORD)
    {
        if (hwnd != gGameWnd) return;
        if (idObject != OBJID_WINDOW || idChild != CHILDID_SELF) return;
        if (event == EVENT_OBJECT_LOCATIONCHANGE) SyncToGameWindowNow();
    }

    void CALLBACK MoveSizeProc(HWINEVENTHOOK, DWORD event, HWND hwnd, LONG, LONG, DWORD, DWORD)
    {
        if (hwnd != gGameWnd) return;
        if (event == EVENT_SYSTEM_MOVESIZESTART) gIsMoving = true;
        if (event == EVENT_SYSTEM_MOVESIZEEND)   gIsMoving = false;
    }

    void InstallWinEventHooks()
    {
        if (!gLocHook) {
            DWORD pid = 0, tid = GetWindowThreadProcessId(gGameWnd, &pid);
            gLocHook = SetWinEventHook(EVENT_OBJECT_LOCATIONCHANGE, EVENT_OBJECT_LOCATIONCHANGE,
                nullptr, LocEventProc, pid, tid,
                WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
        }
        if (!gMoveHook) {
            DWORD pid = 0, tid = GetWindowThreadProcessId(gGameWnd, &pid);
            gMoveHook = SetWinEventHook(EVENT_SYSTEM_MOVESIZESTART, EVENT_SYSTEM_MOVESIZEEND,
                nullptr, MoveSizeProc, pid, tid,
                WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
        }
    }

    LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l)
    {
        if (gReady && ImGui_ImplWin32_WndProcHandler(h, m, w, l)) return 1;

        switch (m) {
        case WM_NCHITTEST: {
            ImGuiIO* pio = gReady ? &ImGui::GetIO() : nullptr;
            bool wantMouse = pio && (settings::gui::menu);
            if (!wantMouse) return HTTRANSPARENT;
            return DefWindowProc(h, m, w, l);
        }
        case WM_SIZE: {
            if (w == SIZE_MINIMIZED) { gMinimized = true; return 0; }
            gMinimized = false;
            int nw = LOWORD(l), nh = HIWORD(l);
            if (nw > 0 && nh > 0) ResizeAll(nw, nh);
            return 0;
        }
        case WM_DESTROY: gRun = false; PostQuitMessage(0); return 0;
        case WM_ERASEBKGND: return 1;
        default: return DefWindowProc(h, m, w, l);
        }
    }

    bool CreateOverlayWindow()
    {
        WNDCLASSEX wc{ sizeof(wc) };
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.lpszClassName = "ULWOverlayClass";
        RegisterClassEx(&wc);

        RECT r{}; if (!GetWindowRect(gGameWnd, &r)) r = { 100,100,1000,700 };
        gOverlayWnd = CreateWindowEx(
            WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_NOACTIVATE,
            wc.lpszClassName, "",
            WS_POPUP | WS_VISIBLE,
            r.left, r.top, r.right - r.left, r.bottom - r.top,
            nullptr, nullptr, wc.hInstance, nullptr);
        if (!gOverlayWnd) return false;

        SetWindowLongPtr(gOverlayWnd, GWLP_HWNDPARENT, (LONG_PTR)gGameWnd);
        ShowWindow(gOverlayWnd, SW_SHOW);
        UpdateWindow(gOverlayWnd);
        return true;
    }


  

    void UpdateClickThroughStyle(bool wantMouse)
    {
        LONG_PTR ex = GetWindowLongPtr(gOverlayWnd, GWL_EXSTYLE);
        bool hasTransparent = (ex & WS_EX_TRANSPARENT) != 0;
        if (!wantMouse && !hasTransparent) {
            SetWindowLongPtr(gOverlayWnd, GWL_EXSTYLE, ex | WS_EX_TRANSPARENT);
        }
        else if (wantMouse && hasTransparent) {
            SetWindowLongPtr(gOverlayWnd, GWL_EXSTYLE, ex & ~WS_EX_TRANSPARENT);
        }
    }

    bool InitAll()
    {
        if (!FindGame()) return false;
        if (!CreateOverlayWindow()) return false;
        settings::gui::screen_size = { (float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN) }; 

        RECT cr{}; GetClientRect(gOverlayWnd, &cr);
        int w = cr.right - cr.left;
        int h = cr.bottom - cr.top;
        if (!CreateD3D(w, h)) return false;
        if (!CreateDIB(w, h)) return false;

        IMGUI_CHECKVERSION(); ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        ImGui::StyleColorsDark();
        ImGuiStyle& st = ImGui::GetStyle();
        st.Alpha = 1.0f;

        GUI::get().initialize(gDev.Get());
        ImGui_ImplWin32_Init(gOverlayWnd);
        ImGui_ImplDX11_Init(gDev.Get(), gCtx.Get());

        gReady = true;
        InstallWinEventHooks();
        PrimeULW();
        return true;
    }
    DWORD old_type_screen = WDA_NONE;

    void RenderFrame()
    {
        if (gMinimized || gW <= 0 || gH <= 0) { Sleep(16); return; }

        if (gIsMoving) SyncToGameWindowNow();

        D3D11_VIEWPORT vp{};
        vp.TopLeftX = 0.0f; vp.TopLeftY = 0.0f;
        vp.Width = (float)gW; vp.Height = (float)gH;
        vp.MinDepth = 0.0f; vp.MaxDepth = 1.0f;
        gCtx->RSSetViewports(1, &vp);

        const float clear[4] = { 0,0,0,0 };
        gCtx->OMSetRenderTargets(1, gRTV.GetAddressOf(), nullptr);
        gCtx->ClearRenderTargetView(gRTV.Get(), clear);

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        imgui_render();
        if (settings::gui::menu) GUI::get().draw();

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        CopyRTtoDIB_Direct();
        ULWPresent();

        ImGuiIO& io = ImGui::GetIO();
        bool wantMouse = (io.WantCaptureMouse || settings::gui::menu);
        UpdateClickThroughStyle(wantMouse);

        DWORD desired = settings::gui::off_screen_bypass ? WDA_NONE : WDA_EXCLUDEFROMCAPTURE;
        if (desired != old_type_screen) {
            if (settings::gui::off_screen_bypass) {
                SetWindowDisplayAffinity(gOverlayWnd, WDA_NONE);
                old_type_screen = WDA_NONE;
            }
            else {
                SetWindowDisplayAffinity(gOverlayWnd, WDA_EXCLUDEFROMCAPTURE);
                old_type_screen = WDA_EXCLUDEFROMCAPTURE;
            }
        }
    }

    DWORD WINAPI ThreadProc(LPVOID)
    {
        if (!InitAll()) return 0;
        MSG msg{};
        while (gRun) {
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg); DispatchMessage(&msg);
                if (msg.message == WM_QUIT) gRun = false;
            }
            if (!gRun) break;
            RenderFrame();

            static bool is_down = false;
            if (GetAsyncKeyState(settings::gui::key)) is_down = true;
            else if (!GetAsyncKeyState(settings::gui::key) && is_down) { is_down = false; settings::gui::menu = !settings::gui::menu; }
        }
        if (gReady) {
            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();
            gReady = false;
        }
        if (gLocHook) { UnhookWinEvent(gLocHook);  gLocHook = nullptr; }
        if (gMoveHook) { UnhookWinEvent(gMoveHook); gMoveHook = nullptr; }
        DestroyDIB();
        DestroyD3D();
        if (gOverlayWnd) {
            SetWindowDisplayAffinity(gOverlayWnd, 0);
            DestroyWindow(gOverlayWnd);
            gOverlayWnd = nullptr;
        }
        return 0;
    }
}

HANDLE Thread;

HANDLE StartThread(HMODULE selfModule)
{
    gSelfModule = selfModule;
    gRun = true;
    DWORD tid = 0;
    Thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)ThreadProc, nullptr, 0, &tid);
    return Thread;
}

void RequestStop()
{
    gRun = false;
    if (gOverlayWnd) PostMessage(gOverlayWnd, WM_CLOSE, 0, 0);
    DestroyDIB();
    DestroyD3D();
    if (Thread) {
        CloseHandle(Thread);
        Thread = nullptr;
    }
    PostQuitMessage(0);
}

bool IsRunning() { return gRun; }
