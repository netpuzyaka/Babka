#include "includes.h"
void cheat_init() {
    il2cpp::init();
    Offsets::Dump();
}
void InitDebugConsole() {
    if (AllocConsole()) {
        FILE* pCout;
        FILE* pCin;
        FILE* pCerr;

        freopen_s(&pCout, "CONOUT$", "w", stdout);
        freopen_s(&pCin, "CONIN$", "r", stdin);
        freopen_s(&pCerr, "CONOUT$", "w", stderr);

        std::ios::sync_with_stdio(true);
        std::cin.clear();
        std::cout.clear();
        std::cerr.clear();

        SetConsoleTitleA("Debug Console");
    }
}

BOOL APIENTRY DllMain(HMODULE h, DWORD reason, LPVOID) {
    InitDebugConsole();
    InstallBypass();
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(h);
        cheat_init();
        StartThread(h);   
    }
    else if (reason == DLL_PROCESS_DETACH) {
        RequestStop();            
    }
    return TRUE;
}
