#include "Utils/Il2cpp/lazy_importer.hpp"
#include <d3d11.h>
//#include <D3DX11.h>
#pragma comment (lib, "d3dx11.lib")
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WndProcHook(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//	g_KeyManager::HandleMessage(uMsg, wParam);

	if (show && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	static auto is_down = true;
	static auto is_clicked = false;

	if (GetAsyncKeyState(VK_INSERT))
	{
		is_clicked = false;
		is_down = true;
	}
	else if (!GetAsyncKeyState(VK_INSERT) && is_down)
	{
		is_clicked = true;
		is_down = false;
	}
	else
	{
		is_clicked = false;
		is_down = false;
	}

	if (is_clicked)
	{
		show = !show;
	}
	auto pressed_buttons = false;
	auto pressed_menu_key = uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_MOUSEWHEEL;

	if (!pressed_menu_key)
		pressed_buttons = true;
	if (!pressed_buttons && show && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(original_windowproc, hWnd, uMsg, wParam, lParam);
}
HRESULT resize_hook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {

	if (render_target_view) render_target_view->Release();

	if (immediate_context) immediate_context->Release();
	if (device) device->Release();

	device = nullptr;

	return resize_original(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}
HRESULT present_hook(IDXGISwapChain* swapChain, UINT SyncInterval, UINT Flags) {


	if (!device) {
		swapChain->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device));
		device->GetImmediateContext(&immediate_context);
		ID3D11Texture2D* renderTarget = nullptr;
		swapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<PVOID*>(&renderTarget));
		device->CreateRenderTargetView(renderTarget, nullptr, &render_target_view);
		renderTarget->Release();
		ImGui::CreateContext();

		ImGui_ImplWin32_Init(game_window);
		ImGui_ImplDX11_Init(device, immediate_context);
		ImGuiIO& io = ImGui::GetIO();
		ImFontConfig cfg;
		cfg.FontBuilderFlags != ImGuiFreeTypeBuilderFlags::ImGuiFreeTypeBuilderFlags_NoHinting;
		ImFontConfig cfg2;
		cfg2.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags::ImGuiFreeTypeBuilderFlags_Bold;
		ImGuiStyle& style = ImGui::GetStyle();

		style.WindowRounding = 6;
		style.ChildRounding = 3;
		style.FrameRounding = 3;
		style.PopupRounding = 3;
		style.GrabRounding = 3;
		style.TabRounding = 3;
		style.ScrollbarRounding = 3;
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.WindowTitleAlign = { 0.5f, 0.5f };
		style.ItemSpacing = { 8.0f, 8.0f };
		style.WindowPadding = { 8.0f, 8.0f };
		style.FramePadding = { 4.0f, 2.0f };
		style.WindowBorderSize = 1;
		style.FrameBorderSize = 0;
		style.ScrollbarSize = 2.f;
		style.GrabMinSize = 8.f;

		style.Colors[ImGuiCol_WindowBg] = ImAdd->Hex2RGBA(0x121212, 1.0f);
		style.Colors[ImGuiCol_PopupBg] = ImAdd->Hex2RGBA(0x121212, 1.0f);
		style.Colors[ImGuiCol_TitleBg] = ImAdd->Hex2RGBA(0x000000, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = ImAdd->Hex2RGBA(0x181818, 1.0f);
		style.Colors[ImGuiCol_ChildBg] = ImAdd->Hex2RGBA(0x181818, 1.0f);
		style.Colors[ImGuiCol_Button] = ImAdd->Hex2RGBA(0x2F2F2F, 1.0f);
		style.Colors[ImGuiCol_ButtonHovered] = ImAdd->Hex2RGBA(0x444444, 1.0f);
		style.Colors[ImGuiCol_ButtonActive] = ImAdd->Hex2RGBA(0x363636, 1.0f);
		style.Colors[ImGuiCol_Text] = ImAdd->Hex2RGBA(0xfafafa, 1.0f);
		style.Colors[ImGuiCol_TextDisabled] = ImAdd->Hex2RGBA(0x808080, 1.0f);
		style.Colors[ImGuiCol_Border] = ImAdd->Hex2RGBA(0x2b2b2b, 1.0f);
		style.Colors[ImGuiCol_Separator] = ImAdd->Hex2RGBA(0x2b2b2b, 1.0f);

		style.Colors[ImGuiCol_FrameBg] = ImAdd->Hex2RGBA(0x2F2F2F, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImAdd->Hex2RGBA(0x444444, 1.0f);
		style.Colors[ImGuiCol_FrameBgActive] = ImAdd->Hex2RGBA(0x363636, 1.0f);
		style.Colors[ImGuiCol_CheckMark] = ImAdd->Hex2RGBA(0xfafafa, 1.0f);

		style.Colors[ImGuiCol_SliderGrab] = ImAdd->Hex2RGBA(0x7682FF, 1.0f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImAdd->Hex2RGBA(0x212121, 1.0f);

		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
		static const ImWchar icons_ranges_brands[] = { ICON_MIN_FAB, ICON_MAX_16_FAB, 0 };
		ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
		ImFont* font = io.Fonts->AddFontFromMemoryTTF(&museo_700_binary, sizeof museo_700_binary, 14, NULL, io.Fonts->GetGlyphRangesDefault());
		io.Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 14.f, &icons_config, icons_ranges);
		io.Fonts->AddFontFromMemoryCompressedTTF(fa_brands_400_compressed_data, fa_brands_400_compressed_size, 14.f, &icons_config, icons_ranges_brands);
		Small_fonts = io.Fonts->AddFontFromMemoryTTF(smallestpixel7, sizeof(smallestpixel7), 10.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
		DefaultFonts = io.Fonts->AddFontFromMemoryTTF(opensans, sizeof(opensans), 13.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

		static bool inited = false;
		if (!inited) {
			CreateDirectoryA(
				("Sky.one"), NULL);
			config.Initialize();
			inited = true;
		}
	}

	immediate_context->OMSetRenderTargets(1, &render_target_view, nullptr);
	immediate_context->RSGetViewports(&vps, &viewport);
	screen_size = { viewport.Width, viewport.Height };
	screen_center = { viewport.Width / 2.0f, viewport.Height / 2.0f };
	vars::stuff::ScreenHeight = viewport.Height;
	vars::stuff::ScreenWidth = viewport.Width;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	g_Render->BeginScene();

	g_Render->EndScene();

	if (show) net_menu();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	if (vars::stuff::Panic) {
		LocalPlayer::Entity()->unloadadm();
		config.Load("");
		MH_DisableHook(MH_ALL_HOOKS);
	}

	return present_original(swapChain, SyncInterval, Flags);
}
uintptr_t find_pattern(uintptr_t base, const PBYTE Pattern, const char* Mask) {
	PBYTE Start = (PBYTE)base;
	PIMAGE_NT_HEADERS NTHead = (PIMAGE_NT_HEADERS)(Start + ((PIMAGE_DOS_HEADER)Start)->e_lfanew);
	DWORD Len = NTHead->OptionalHeader.SizeOfImage;

	for (PBYTE region_it = Start; region_it < (Start + Len); ++region_it) {
		if (*region_it == *Pattern) {
			bool found = true;
			const unsigned char* pattern_it = Pattern, * mask_it = (const PBYTE)Mask, * memory_it = region_it;
			for (; *mask_it && (memory_it < (Start + Len)); ++mask_it, ++pattern_it, ++memory_it) {
				if (*mask_it != 'x') continue;
				if (*memory_it != *pattern_it) {
					found = false;
					break;
				}
			}

			if (found)
				return (uintptr_t)region_it;
		}
	}

	return 0;
}


void hk2_(void* Function, void** Original, void* Detour) {
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED) {
		return;
	}
	MH_CreateHook(Function, Detour, Original);
	MH_EnableHook(Function);
}
void Start() {
	InGame::stor::gBase = (DWORD64)GetModuleHandleA(("GameAssembly.dll"));
	InGame::stor::uBase = (DWORD64)GetModuleHandleA(("UnityPlayer.dll"));
	il2cpp::init();

	while (!game_window) {
		EnumWindows([](HWND hWnd, LPARAM lParam) -> BOOL {
			DWORD pid = 0;
			GetWindowThreadProcessId(hWnd, &pid);
			if (pid == GetCurrentProcessId()) {
				*reinterpret_cast<HWND*>(lParam) = hWnd;
				return FALSE;
			}

			return TRUE;
			}, reinterpret_cast<LPARAM>(&game_window));
	}
	IDXGISwapChain* swapChain = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	auto featureLevel = D3D_FEATURE_LEVEL_11_0;

	DXGI_SWAP_CHAIN_DESC sd = { 0 };
	ZeroMemory(&sd, sizeof sd);
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = game_window;
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 0, &featureLevel, 1, D3D11_SDK_VERSION, &sd, &swapChain, &device, nullptr, &context))) {
		MessageBoxW(0, (L"Failed to create D3D11 device and swap chain"), (L"Failure"), MB_ICONERROR);
	}
	else {
		auto table = *reinterpret_cast<PVOID**>(swapChain);
		present_original = reinterpret_cast<HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT)>(table[8]);
		resize_original = reinterpret_cast<HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT)>(table[13]);

		context->Release();
		device->Release();
		swapChain->Release();

		original_windowproc = (WNDPROC)SetWindowLongPtrW(game_window, GWLP_WNDPROC, (LONG_PTR)WndProcHook);

		hk2_((void*)table[8], (void**)&present_original, present_hook);
		hk2_((void*)table[13], (void**)&resize_original, resize_hook);

	}
}
