#define _CRT_SECURE_NO_WARNINGS
#define IMGUI_DEFINE_MATH_OPERATORS
#pragma comment(lib, "D3DX11.lib")
#pragma comment(lib, "Winmm.lib")
#include <Windows.h>
#include <filesystem>
#include "thread"
#include <iostream>
#include <d3d11.h>
#include <dxgi.h>
#include <string>
#include <Lmcons.h>
#include <TlHelp32.h>
#include <vector>
// CStringA replacement — no MFC/ATL needed (project uses /clr:none, afx.h/atlstr.h unavailable)
inline std::string WideToAnsi(LPCWSTR wstr)
{
	if (!wstr) return std::string();
	int len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
	if (len <= 0) return std::string();
	std::string out(len - 1, '\0');
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, out.data(), len, nullptr, nullptr);
	return out;
}
#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
static float color[4] = { 124 / 255.f, 103 / 255.f, 255 / 255.f, 1.f };
#include "imgui/imgui_edited.hpp"
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11ShaderResourceView* preview_slow = nullptr;
ID3D11ShaderResourceView* kakrazz = nullptr;
ID3D11RenderTargetView* mainRenderTargetView;
namespace font
{
	inline ImFont* default_font = nullptr;
	inline ImFont* good_font = nullptr;
	inline ImFont* roboto = nullptr;
}
#include "main/auth/sk.h"
#include "main/utils/math/vector.h"
#include "main/utils/math/crc32.h"
#include "main/utils/math/math.h"
#include "kiero/bytes.h"
#include "kiero/minhook/include/MinHook.h"
#include "main/utils/settings.h"
#include "main/utils/config/config.h"
#include "main/utils/il2cpp/Memory.h"
#include "main/utils/il2cpp/il2cpp.h"
#include "main/cheat/offsets.h"
#include "main/utils/func.h"
#include "main/utils/sdk.h"
#include "main/cheat/hooks.h"
#include "main/cheat/visuals/rendering.h"
#include "main/cheat/visuals/enity_loop.h"

#include "main/discord_rpc/discord_rpc_init.h"

Discord* g_Discord;

#include "main/menu.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;