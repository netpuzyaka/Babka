#pragma warning(disable : 4530)
#define _CRT_SECURE_NO_WARNINGS

#define StrA
#define StrW

#define noauth
//#define disable

#include <stdint.h>
#include <Windows.h>
#include <psapi.h>
#include <d3d11.h>
#include <string>
#include <codecvt>
#include <locale>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <emmintrin.h>
#include "winternl.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "Cheat/Hooks/offsets.h"
#include "Utils/Math/crc32.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <thread>
#include "Utils/xorstr.h"
#include <comdef.h>
#include "Cheat/Visuals/menu/imgui/imgui.h"
#include <Lmcons.h>
#include "Utils/Il2cpp/Memory.h"
#include "Utils/Math/structs.h"
#include "Utils/Math/vector.h"
#include "Utils/Math/math.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "Cheat/Visuals/menu/imgui/imgui_freetype.h"
#include "Cheat/Visuals/menu/imgui/imgui_impl_win32.h"
#include "Cheat/Visuals/menu/imgui/imgui_impl_dx11.h"
#include "Cheat/Visuals/menu/imgui/imgui_internal.h"
#include <string_view>
#include <unordered_map>
ImFont* Small_fonts;
ImFont* DefaultFonts;

ImFont* flogs;

ImFont* Icons;

int font_size = 12;

#include "Utils/vars.h"
#include "Utils/class.h"
#include "Utils/Il2cpp/il2cpp.h"
#include "Cheat/Game/game.h"
#include "Utils/Fonts.h"
#include "Cheat/Visuals/menu/Elements/ImAdd.h"

ID3D11ShaderResourceView* Logotype = nullptr;
static ImVec2 menu_size = ImVec2(495, 540);
static ImVec2 prev_size = ImVec2(200, 350);
HWND game_window;
HRESULT(*present_original)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
HRESULT(*resize_original)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;
ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediate_context = nullptr;
ID3D11RenderTargetView* render_target_view = nullptr;
Vector2 screen_size = { 0, 0 };
D3D11_VIEWPORT viewport;
UINT vps = 1;
WNDPROC original_windowproc = nullptr;
namespace belt {
	Vector2 pos = Vector2(200, 200);
	bool should_drag = false;
	bool should_move = false;

	POINT cursor;
	POINT cursor_corrected;
	void belt_tab_mov(Vector2 size) {
		GetCursorPos(&cursor);

		if (GetAsyncKeyState(VK_LBUTTON) && (cursor.x > pos.x && cursor.y > pos.y && cursor.x < pos.x + size.x && cursor.y < pos.y + size.y)) {
			should_drag = true;
			if (!should_move) {
				cursor_corrected.x = cursor.x - pos.x;
				cursor_corrected.y = cursor.y - pos.y;
				should_move = true;
			}
		}

		if (should_drag) {
			pos.x = cursor.x - cursor_corrected.x;
			pos.y = cursor.y - cursor_corrected.y;
		}

		if (GetAsyncKeyState(VK_LBUTTON) == 0) {
			should_drag = false;
			should_move = false;
		}
	}
}
float size_name = 15.f;
#include "Utils/WepaonIcon.h"
#include "Cheat/Render.h"
#include "Cheat/Hooks/minhook/include/MinHook.h"
#include "Cheat/Visuals/Hitmarker/HitMarker.h"
#include "Cheat/Misc/aim.h"
#include "Cheat/Misc/misc.h"
#include "Cheat/Misc/other.hpp"
#include "Cheat/Visuals/esp.h"
#include "Cheat/Hooks/hooks.h"
#include "Cheat/Game/entities.h"
#include "Cheat/Config/Config.h"
#include "Cheat/Visuals/Rendering.h"
#include "Cheat/Visuals/menu/Menu.h"
#include "Startup.h"
#pragma comment(lib, "winmm.lib")