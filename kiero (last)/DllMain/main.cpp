#include "includes.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc = NULL;
volatile bool g_panic_unload = false;   // panic-requested (checked in hooks)
volatile bool g_hooks_active = false;   // il2cpp hooks are installed
volatile bool g_ready_for_render = false; // MainThread finished init; ImGui may start

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImFontConfig cfg;
	font::lexend_general_bold = io.Fonts->AddFontFromMemoryTTF(lexend_bold, sizeof(lexend_bold), 18.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	font::lexend_general_bold_2 = io.Fonts->AddFontFromMemoryTTF(lexend_bold, sizeof(lexend_bold), 34.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::lexend_bold = io.Fonts->AddFontFromMemoryTTF(lexend_regular, sizeof(lexend_regular), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::lexend_regular = io.Fonts->AddFontFromMemoryTTF(lexend_regular, sizeof(lexend_regular), 14.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icomoon = io.Fonts->AddFontFromMemoryTTF(icomoon, sizeof(icomoon), 20.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

    font::icomoon_widget = io.Fonts->AddFontFromMemoryTTF(icomoon_widget, sizeof(icomoon_widget), 15.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icomoon_widget2 = io.Fonts->AddFontFromMemoryTTF(icomoon, sizeof(icomoon), 16.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	font::default_font = io.Fonts->AddFontFromMemoryTTF(cunia, sizeof(cunia), 12.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	font::good_font = io.Fonts->AddFontFromMemoryTTF(segue, sizeof(segue), 12.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	font::roboto = io.Fonts->AddFontFromMemoryTTF(roboto, sizeof(roboto), 12.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };
	D3DX11CreateShaderResourceViewFromMemory(pDevice, spike, sizeof(spike), &info, pump, &preview_slow, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, kokrazz, sizeof(kokrazz), &info, pump, &kakrazz, 0);
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// ImGui «съедает» только те сообщения, которые реально обработал его хендлер.
	// Раньше здесь возвращался `true` (=1) как LRESULT для любого msg — это ломало
	// ввод игры (зависание курсора/кликов при открытом меню).
	if (!g_panic_unload && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return TRUE;

	// Panic: немедленно вернуть родной WndProc, чтобы не ловить сообщения
	// через уже деактивированный детюр до пересоздания окна в hkPresent.
	if (g_panic_unload && oWndProc)
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

void open_menu() {
	static auto is_down = false;
	if (GetAsyncKeyState(VK_INSERT))is_down = true;
	else if (!GetAsyncKeyState(VK_INSERT) && is_down) { is_down = false; settings::menu::show = !settings::menu::show; }
	// Panic: не ставим флаг в каждом кадре повторно; хуки сами само-отключатся по g_panic_unload,
	// полный откат делает hkPresent. Повторное нажатие после отката ничего не сломает.
	if (GetAsyncKeyState(VK_END) && !settings::menu::panic && !g_panic_unload) {
		settings::menu::panic = true;
		g_panic_unload = true;
	}
}

HRESULT(__stdcall* oResizeBuffers)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
HRESULT hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (mainRenderTargetView) {
		pContext->OMSetRenderTargets(0, 0, 0);
		mainRenderTargetView->Release();
	}
	HRESULT hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	ID3D11Texture2D* pBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
	pDevice->CreateRenderTargetView(pBuffer, NULL, &mainRenderTargetView);
	pBuffer->Release();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	D3D11_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1, &vp);
	return hr;
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	// === Panic/unload: полный откат всех подсистем в потоке рендера ===
	if (g_panic_unload)
	{
		g_panic_unload = false;
		settings::menu::panic = false;
		settings::menu::show = false;

		// 1. Снять il2cpp-хуки (MinHook) — пока мы в Present, игровые потоки не исполняют детуры.
		if (g_hooks_active) {
			hooks_unload();
			g_hooks_active = false;
		}

		// 2. Вернуть родной WndProc
		if (window && oWndProc) {
			SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
			oWndProc = NULL;
		}

		// 3. Деинициализация ImGui/DX11 до освобождения RTV
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		// 4. Отвязать DXGI-хуки kiero (Present/ResizeBuffers)
		kiero::shutdown();

		// 5. Освободить наши DX-ресурсы
		if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = nullptr; }
		if (pContext) { pContext->Release(); pContext = nullptr; }
		if (pDevice) { pDevice->Release(); pDevice = nullptr; }
		window = NULL;
		init = false;

		return oPresent(pSwapChain, SyncInterval, Flags);
	}

	// Не трогать il2cpp/ImGui, пока MainThread не завершил подготовку
	// (раньше здесь был busy-wait без sleep — он и вешал игру при обычном инжекте).
	if (!g_ready_for_render)
		return oPresent(pSwapChain, SyncInterval, Flags);

	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			kiero::unbind(13);
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}
		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	open_menu();
	// ESP-рендер обращается к il2cpp-объектам: пропускаем только при живых хуках
	if (g_hooks_active)
		esp_render();
	if (settings::menu::watermark) watermark();
	if (settings::menu::show) menu();

	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	// Ждём, пока Rust реально загрузит GameAssembly.dll и поднимет il2cpp-домен.
	// Без этого цикла (или с busy-wait без Sleep) инжект «на горячую» либо зависает,
	// либо обрывается — именно это давало «зависание при обычном инжекте».
	HMODULE ga = NULL;
	for (int i = 0; i < 120 && !ga; ++i) // до ~60 секунд
	{
		ga = GetModuleHandleA(skCrypt("GameAssembly.dll"));
		if (!ga) Sleep(500);
	}
	if (!ga) return FALSE; // игра закрылась раньше — тихо выходим, не вешая процесс

	// Проверка готовности домена: на раннем этапе домен ещё null — ждём.
	// (il2cpp_domain_get()==0 -> assemblies() читает nullptr+смещение -> AV -> «игра закрывается» при ManualMap)
	for (int i = 0; i < 60; ++i)
	{
		uintptr_t domain = reinterpret_cast<uintptr_t(*)()>(GetProcAddress(ga, skCrypt("il2cpp_domain_get")))();
		if (domain) break;
		Sleep(500);
	}

	// Подготовка SDK/хуков в SEH-обёртке: если сигнатуры метода не совпали с текущим
	// билдом игры — перехватываем AV вместо падения процесса (ManualMap-краш).
	bool sdk_ok = false;
	__try {
		settings::gBase = il2cpp::GetModuleBase(L"GameAssembly.dll");
		il2cpp::init();
		find_offsets();
		sdk_ok = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		sdk_ok = false;
	}
	if (!sdk_ok) return FALSE;

	hooks_load();
	g_hooks_active = true;

	config.Initialize();
	settings::screen_size = { (float)GetSystemMetrics(SM_CXSCREEN),(float)GetSystemMetrics(SM_CYSCREEN) };

	// Инициализация kiero с паузами вместо бесконечного busy-wait
	while (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success)
		Sleep(500);

	kiero::bind(8, (void**)&oPresent, hkPresent);
	kiero::bind(13, (void**)&oResizeBuffers, hkResizeBuffers);

	g_ready_for_render = true; // можно включать ImGui в Present
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		// Каталоги создаёт MainThread (DllMain под loader-lock нельзя тянуть с CreateDirectory+skCrypt-статикой)
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		// Только снятие хуков — никаких блокирующих вызовов под loader-lock
		if (g_hooks_active) {
			MH_DisableHook(MH_ALL_HOOKS);
			MH_Uninitialize();
			g_hooks_active = false;
		}
		if (window && oWndProc) {
			SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
		}
		kiero::shutdown();
		break;
	}
	return TRUE;
}
