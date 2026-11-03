#define NOMINMAX
#include <windows.h>
#include <winreg.h>
#include <iphlpapi.h>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdarg>
#include <io.h>
#include <fcntl.h>
#include <TlHelp32.h>
#include <psapi.h>
#include <ntstatus.h>

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "advapi32.lib")


typedef LSTATUS(WINAPI* RegOpenKeyExW_t)(HKEY, LPCWSTR, DWORD, REGSAM, PHKEY);
typedef LSTATUS(WINAPI* RegOpenKeyExA_t)(HKEY, LPCSTR, DWORD, REGSAM, PHKEY);
typedef LSTATUS(WINAPI* RegCreateKeyExW_t)(HKEY, LPCWSTR, DWORD, LPWSTR, DWORD, REGSAM, LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD);
typedef LSTATUS(WINAPI* RegCreateKeyExA_t)(HKEY, LPCSTR, DWORD, LPSTR, DWORD, REGSAM, LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD);
typedef LSTATUS(WINAPI* RegSetValueExW_t) (HKEY, LPCWSTR, DWORD, DWORD, const BYTE*, DWORD);
typedef LSTATUS(WINAPI* RegSetValueExA_t) (HKEY, LPCSTR, DWORD, DWORD, const BYTE*, DWORD);

typedef BOOL(WINAPI* GetVolumeInformationW_t)(LPCWSTR, LPWSTR, DWORD, LPDWORD, LPDWORD, LPDWORD, LPWSTR, DWORD);
typedef BOOL(WINAPI* GetVolumeInformationA_t)(LPCSTR, LPSTR, DWORD, LPDWORD, LPDWORD, LPDWORD, LPSTR, DWORD);
typedef BOOL(WINAPI* GetVolumeInformationByHandleW_t)(HANDLE, LPWSTR, DWORD, LPDWORD, LPDWORD, LPDWORD, LPWSTR, DWORD);
typedef ULONG(WINAPI* GetAdaptersInfo_t)(PIP_ADAPTER_INFO, PULONG);

typedef BOOL(WINAPI* GetFileAttributesExW_t)(LPCWSTR, GET_FILEEX_INFO_LEVELS, LPVOID);
typedef HANDLE(WINAPI* FindFirstFileExW_t)(LPCWSTR, FINDEX_INFO_LEVELS, LPVOID, FINDEX_SEARCH_OPS, LPVOID, DWORD);
typedef HANDLE(WINAPI* FindFirstFileW_t)(LPCWSTR, LPWIN32_FIND_DATAW);
typedef BOOL(WINAPI* FindNextFileW_t)(HANDLE, LPWIN32_FIND_DATAW);

typedef BOOL(WINAPI* GetFileAttributesExA_t)(LPCSTR, GET_FILEEX_INFO_LEVELS, LPVOID);
typedef HANDLE(WINAPI* FindFirstFileExA_t)(LPCSTR, FINDEX_INFO_LEVELS, LPVOID, FINDEX_SEARCH_OPS, LPVOID, DWORD);
typedef HANDLE(WINAPI* FindFirstFileA_t)(LPCSTR, LPWIN32_FIND_DATAA);
typedef BOOL(WINAPI* FindNextFileA_t)(HANDLE, LPWIN32_FIND_DATAA);

typedef HANDLE(WINAPI* CreateFileW_t)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef HANDLE(WINAPI* CreateFileA_t)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

typedef BOOL(WINAPI* GetWindowDisplayAffinity_t)(HWND, DWORD*);

typedef VOID(WINAPI* GetSystemInfo_t)(LPSYSTEM_INFO);
typedef VOID(WINAPI* GetNativeSystemInfo_t)(LPSYSTEM_INFO);

typedef BOOL(WINAPI* GlobalMemoryStatusEx_t)(LPMEMORYSTATUSEX);
typedef NTSTATUS(NTAPI* NtQueryInformationThread_t)(HANDLE, THREADINFOCLASS, PVOID, ULONG, PULONG);
typedef void* (__cdecl* GetCurrentDomain_t)();
typedef void* (__cdecl* GetAssemblies_t)(void*);
typedef void* (__cdecl* GetExecutingAssembly_t)();
typedef void(__cdecl* ProcessKill_t)();
typedef void(__cdecl* EnvironmentFailFast_t)(void*);


static GetCurrentDomain_t g_GetCurrentDomain = nullptr;
static GetAssemblies_t g_GetAssemblies = nullptr;
static GetExecutingAssembly_t g_GetExecutingAssembly = nullptr;
static ProcessKill_t g_ProcessKill = nullptr;
static EnvironmentFailFast_t g_EnvironmentFailFast = nullptr;

static NtQueryInformationThread_t g_NtQueryInformationThread = nullptr;
struct Il2CppString { void* klass; void* monitor; int32_t length; wchar_t start_char[1]; };
using Il2CppMethodPointer = void(*)();
using il2cpp_resolve_icall_t = Il2CppMethodPointer(__cdecl*)(const char*);
using il2cpp_string_new_t = Il2CppString * (__cdecl*)(const char*);
using GetDeviceUniqueIdentifier_t = Il2CppString * (__cdecl*)();

using GetProcessorType_t = Il2CppString * (__cdecl*)();
using GetProcessorFrequencyMHz_t = int(__cdecl*)();
using GetProcessorCount_t = int(__cdecl*)();
using GetPhysicalMemoryMB_t = int(__cdecl*)();
using GetDeviceName_t = Il2CppString * (__cdecl*)();
using GetDeviceModel_t = Il2CppString * (__cdecl*)();
using GetDeviceType_t = int(__cdecl*)();
using GetGraphicsMemorySize_t = int(__cdecl*)();
using GetGraphicsDeviceName_t = Il2CppString * (__cdecl*)();
using GetGraphicsDeviceVendor_t = Il2CppString * (__cdecl*)();
typedef SIZE_T(WINAPI* VirtualQueryEx_t)(HANDLE, LPCVOID, PMEMORY_BASIC_INFORMATION, SIZE_T);
typedef BOOL(WINAPI* Thread32First_t)(HANDLE, LPTHREADENTRY32);
typedef BOOL(WINAPI* Thread32Next_t)(HANDLE, LPTHREADENTRY32);
typedef BOOL(WINAPI* Process32First_t)(HANDLE, LPPROCESSENTRY32);
typedef BOOL(WINAPI* Process32Next_t)(HANDLE, LPPROCESSENTRY32);
typedef BOOL(WINAPI* Module32First_t)(HANDLE, LPMODULEENTRY32);
typedef BOOL(WINAPI* Module32Next_t)(HANDLE, LPMODULEENTRY32);
typedef HANDLE(WINAPI* CreateToolhelp32Snapshot_t)(DWORD, DWORD);
typedef SIZE_T(WINAPI* VirtualQuery_t)(LPCVOID, PMEMORY_BASIC_INFORMATION, SIZE_T);
typedef BOOL(WINAPI* GetModuleInformation_t)(HANDLE, HMODULE, LPMODULEINFO, DWORD);
typedef BOOL(WINAPI* GetModuleInformation_t)(HANDLE, HMODULE, LPMODULEINFO, DWORD);
typedef BOOL(WINAPI* K32GetModuleInformation_t)(HANDLE, HMODULE, LPMODULEINFO, DWORD);
typedef DWORD(WINAPI* GetModuleFileNameExA_t)(HANDLE, HMODULE, LPSTR, DWORD);
typedef DWORD(WINAPI* GetModuleFileNameExW_t)(HANDLE, HMODULE, LPWSTR, DWORD);
typedef DWORD(WINAPI* GetModuleBaseNameA_t)(HANDLE, HMODULE, LPSTR, DWORD);
typedef DWORD(WINAPI* GetModuleBaseNameW_t)(HANDLE, HMODULE, LPWSTR, DWORD);
typedef BOOL(WINAPI* EnumProcessModules_t)(HANDLE, HMODULE*, DWORD, LPDWORD);
typedef BOOL(WINAPI* EnumProcessModulesEx_t)(HANDLE, HMODULE*, DWORD, LPDWORD, DWORD);

static EnumProcessModules_t g_EnumProcessModules = nullptr;
static EnumProcessModulesEx_t g_EnumProcessModulesEx = nullptr;
static GetModuleInformation_t   g_GetModuleInformation = nullptr;
static K32GetModuleInformation_t g_K32GetModuleInformation = nullptr;
static GetModuleFileNameExA_t   g_GetModuleFileNameExA = nullptr;
static GetModuleFileNameExW_t   g_GetModuleFileNameExW = nullptr;
static GetModuleBaseNameA_t     g_GetModuleBaseNameA = nullptr;
static GetModuleBaseNameW_t     g_GetModuleBaseNameW = nullptr;
static VirtualQueryEx_t g_VirtualQueryEx = nullptr;

static Thread32First_t g_Thread32First = nullptr;
static Thread32Next_t g_Thread32Next = nullptr;
static Process32First_t g_Process32First = nullptr;
static Process32Next_t g_Process32Next = nullptr;
static Module32First_t g_Module32First = nullptr;
static Module32Next_t g_Module32Next = nullptr;
static CreateToolhelp32Snapshot_t g_CreateToolhelp32Snapshot = nullptr;

static RegOpenKeyExW_t    g_RegOpenKeyExW = nullptr;
static RegOpenKeyExA_t    g_RegOpenKeyExA = nullptr;
static RegCreateKeyExW_t  g_RegCreateKeyExW = nullptr;
static RegCreateKeyExA_t  g_RegCreateKeyExA = nullptr;
static RegSetValueExW_t   g_RegSetValueExW = nullptr;
static RegSetValueExA_t   g_RegSetValueExA = nullptr;

static GetSystemInfo_t       g_GetSystemInfo = nullptr;
static GetNativeSystemInfo_t g_GetNativeSystemInfo = nullptr;
static GlobalMemoryStatusEx_t g_GlobalMemoryStatusEx = nullptr;

static GetVolumeInformationW_t         g_OrigGVIW = nullptr;
static GetVolumeInformationA_t         g_OrigGVIA = nullptr;
static GetVolumeInformationByHandleW_t g_OrigGVIByHW = nullptr;
static GetAdaptersInfo_t               g_OrigGAI = nullptr;
static GetWindowDisplayAffinity_t      g_OrigGetWDA = nullptr;

static GetFileAttributesExW_t g_GetFileAttributesExW = nullptr;
static FindFirstFileExW_t     g_FindFirstFileExW = nullptr;
static FindFirstFileW_t       g_FindFirstFileW = nullptr;
static FindNextFileW_t        g_FindNextFileW = nullptr;

static GetFileAttributesExA_t g_GetFileAttributesExA = nullptr;
static FindFirstFileExA_t     g_FindFirstFileExA = nullptr;
static FindFirstFileA_t       g_FindFirstFileA = nullptr;
static FindNextFileA_t        g_FindNextFileA = nullptr;

static CreateFileW_t g_CreateFileW = nullptr;
static CreateFileA_t g_CreateFileA = nullptr;

static GetDeviceUniqueIdentifier_t  g_OrigGetDuid = nullptr;
static il2cpp_string_new_t          g_il2cpp_string_new = nullptr;

static GetProcessorType_t        g_OrigGetProcessorType = nullptr;
static GetProcessorFrequencyMHz_t g_OrigGetProcessorFreq = nullptr;
static GetProcessorCount_t       g_OrigGetProcessorCount = nullptr;
static GetPhysicalMemoryMB_t     g_OrigGetPhysicalMemory = nullptr;
static GetDeviceName_t           g_OrigGetDeviceName = nullptr;
static GetDeviceModel_t          g_OrigGetDeviceModel = nullptr;
static GetDeviceType_t           g_OrigGetDeviceType = nullptr;
static GetGraphicsMemorySize_t   g_OrigGetGraphicsMemory = nullptr;
static GetGraphicsDeviceName_t   g_OrigGetGraphicsName = nullptr;
static GetGraphicsDeviceVendor_t g_OrigGetGraphicsVendor = nullptr;

static volatile LONG g_seedInit = 0;
static UINT32 g_seed = 0;
static void EnsureSeed() {
    if (InterlockedCompareExchange(&g_seedInit, 1, 0) == 0) {
        LARGE_INTEGER qpc{}; QueryPerformanceCounter(&qpc);
        ULONGLONG t = GetTickCount64();
        UINT32 s = (UINT32)(qpc.QuadPart ^ (qpc.QuadPart >> 32)) ^ (UINT32)t ^ (UINT32)(t >> 32) ^ 0x9E3779B9u;
        g_seed = s ? s : 0xA5C35F1u;
    }
}
static inline UINT32 mix32(UINT32 x) {
    x ^= x >> 16; x *= 0x7feb352dU;
    x ^= x >> 15; x *= 0x846ca68bU;
    x ^= x >> 16; return x;
}

static volatile LONG g_consoleInit = 0;
static void EnsureConsole() {
    if (InterlockedCompareExchange(&g_consoleInit, 1, 0) == 0) {
        if (!AttachConsole(ATTACH_PARENT_PROCESS)) AllocConsole();
        SetConsoleOutputCP(CP_UTF8);
        FILE* fp = nullptr;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        _setmode(_fileno(stdout), _O_U8TEXT);
        _setmode(_fileno(stderr), _O_U8TEXT);
        wprintf(L"[hook] console initialized\n");
        fflush(stdout);
    }
}
static void LogW(const wchar_t* fmt, ...) {
    EnsureConsole();
    va_list args; va_start(args, fmt);
    vwprintf(fmt, args);
    va_end(args);
    wprintf(L"\n");
    fflush(stdout);
}

static std::wstring AnsiToWide(const char* s) {
    if (!s) return L"";
    int len = MultiByteToWideChar(CP_ACP, 0, s, -1, nullptr, 0);
    if (len <= 1) return L"";
    std::wstring w(len - 1, L'\0');
    MultiByteToWideChar(CP_ACP, 0, s, -1, &w[0], len);
    return w;
}

static std::wstring MacToStr(const BYTE* mac, UINT len) {
    wchar_t buf[3 * MAX_ADAPTER_ADDRESS_LENGTH + 1] = L"";
    wchar_t* p = buf;
    for (UINT i = 0; i < len && i < MAX_ADAPTER_ADDRESS_LENGTH; i++) {
        _snwprintf_s(p, 4, _TRUNCATE, (i ? L":%02X" : L"%02X"), mac[i]);
        p += (i ? 3 : 2);
    }
    return buf;
}

static std::vector<std::wstring> g_allowRoots;

static std::wstring CanonW(LPCWSTR p) {
    if (!p) return L"";
    wchar_t full[MAX_PATH * 4] = L"";
    GetFullPathNameW(p, (DWORD)std::size(full), full, nullptr);
    for (wchar_t* q = full; *q; ++q) { if (*q == L'/') *q = L'\\'; else *q = (wchar_t)towlower(*q); }
    size_t n = wcslen(full); while (n && full[n - 1] == L'\\') full[--n] = 0;
    return full;
}

static void AddAllowRootIfExists(const std::wstring& path) {
    if (path.empty()) return;
    DWORD a = GetFileAttributesW(path.c_str());
    if (a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY)) g_allowRoots.push_back(path);
}

static std::wstring GetExeDir() {
    wchar_t modPath[MAX_PATH * 4] = L"";
    DWORD n = GetModuleFileNameW(nullptr, modPath, (DWORD)std::size(modPath));
    if (n == 0 || n >= std::size(modPath)) return L"";
    wchar_t* p = modPath + wcslen(modPath);
    while (p > modPath && p[-1] != L'\\' && p[-1] != L'/') --p;
    *p = L'\0';
    return CanonW(modPath);
}

static std::wstring ExpandEnv(const wchar_t* s) {
    wchar_t buf[MAX_PATH * 4] = L"";
    ExpandEnvironmentStringsW(s, buf, (DWORD)std::size(buf));
    return CanonW(buf);
}

static void BuildAllowlistPaths() {
    g_allowRoots.clear();
    AddAllowRootIfExists(GetExeDir());
    g_allowRoots.push_back(CanonW(L"%USERPROFILE%\\AppData\\LocalLow\\Facepunch Studios LTD\\Rust"));
    g_allowRoots.push_back(CanonW(L"C:\\hellhit"));
    g_allowRoots.push_back(CanonW(L"C:\\hellhit\\sounds"));
}

static bool IsUnderAnyAllowed(LPCWSTR path) {
    if (!path) return false;
    std::wstring c = CanonW(path);
    for (auto& root : g_allowRoots) {
        if (c.size() >= root.size() &&
            _wcsnicmp(c.c_str(), root.c_str(), (unsigned)root.size()) == 0 &&
            (c.size() == root.size() || c[root.size()] == L'\\'))
            return true;
    }
    return false;
}

static FILETIME GenerateRandomFileTime() {
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ GetCurrentThreadId() ^ GetTickCount());

    SYSTEMTIME st = { 0 };
    st.wYear = 2018 + (x % 7);
    st.wMonth = 1 + (x >> 4) % 12;
    st.wDay = 1 + (x >> 8) % 28;
    st.wHour = (x >> 12) % 24;
    st.wMinute = (x >> 16) % 60;
    st.wSecond = (x >> 20) % 60;
    st.wMilliseconds = (x >> 24) % 1000;

    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);
    return ft;
}

static inline void ApplyRandomDateTimes(LPWIN32_FIND_DATAW fd) {
    if (!fd) return;
    fd->ftCreationTime = GenerateRandomFileTime();
    fd->ftLastAccessTime = GenerateRandomFileTime();
    fd->ftLastWriteTime = GenerateRandomFileTime();
}

BOOL WINAPI DetourGetFileAttributesExW(LPCWSTR path, GET_FILEEX_INFO_LEVELS lvl, LPVOID info) {
    if (!IsUnderAnyAllowed(path)) { SetLastError(ERROR_ACCESS_DENIED); return FALSE; }
    return g_GetFileAttributesExW(path, lvl, info);
}

HANDLE WINAPI DetourFindFirstFileW(LPCWSTR name, LPWIN32_FIND_DATAW data) {
    if (!IsUnderAnyAllowed(name)) { SetLastError(ERROR_ACCESS_DENIED); return INVALID_HANDLE_VALUE; }
    HANDLE h = g_FindFirstFileW(name, data);
    if (h != INVALID_HANDLE_VALUE && data) {
        ApplyRandomDateTimes(data);
    }
    return h;
}

BOOL WINAPI DetourFindNextFileW(HANDLE h, LPWIN32_FIND_DATAW data) {
    BOOL ok = g_FindNextFileW(h, data);
    if (ok && data) {
        ApplyRandomDateTimes(data);
    }
    return ok;
}

static std::wstring A2W_(LPCSTR s) { return AnsiToWide(s); }

static std::string W2A_(const std::wstring& w) {
    if (w.empty()) return std::string();
    int n = WideCharToMultiByte(CP_ACP, 0, w.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string a; a.resize(n ? n - 1 : 0);
    if (n > 1) WideCharToMultiByte(CP_ACP, 0, w.c_str(), -1, &a[0], n, nullptr, nullptr);
    return a;
}

static void ApplyRandomDateTimesA(LPWIN32_FIND_DATAA fd) {
    if (!fd) return;
    fd->ftCreationTime = GenerateRandomFileTime();
    fd->ftLastAccessTime = GenerateRandomFileTime();
    fd->ftLastWriteTime = GenerateRandomFileTime();
}

BOOL WINAPI DetourGetFileAttributesExA(LPCSTR pathA, GET_FILEEX_INFO_LEVELS lvl, LPVOID info) {
    std::wstring pathW = A2W_(pathA);
    if (!IsUnderAnyAllowed(pathW.c_str())) { SetLastError(ERROR_ACCESS_DENIED); return FALSE; }
    return g_GetFileAttributesExW(pathW.c_str(), lvl, info);
}

HANDLE WINAPI DetourFindFirstFileA(LPCSTR nameA, LPWIN32_FIND_DATAA outA) {
    std::wstring nameW = A2W_(nameA);
    if (!IsUnderAnyAllowed(nameW.c_str())) { SetLastError(ERROR_ACCESS_DENIED); return INVALID_HANDLE_VALUE; }
    WIN32_FIND_DATAW fdw{};
    HANDLE h = g_FindFirstFileW(nameW.c_str(), &fdw);
    if (h != INVALID_HANDLE_VALUE && outA) {
        ApplyRandomDateTimes(&fdw);

        memset(outA, 0, sizeof(*outA));
        outA->dwFileAttributes = fdw.dwFileAttributes;
        outA->ftCreationTime = fdw.ftCreationTime;
        outA->ftLastAccessTime = fdw.ftLastAccessTime;
        outA->ftLastWriteTime = fdw.ftLastWriteTime;
        outA->nFileSizeHigh = fdw.nFileSizeHigh;
        outA->nFileSizeLow = fdw.nFileSizeLow;
        strncpy_s(outA->cFileName, W2A_(fdw.cFileName).c_str(), _TRUNCATE);
        strncpy_s(outA->cAlternateFileName, W2A_(fdw.cAlternateFileName).c_str(), _TRUNCATE);
    }
    return h;
}

BOOL WINAPI DetourFindNextFileA(HANDLE h, LPWIN32_FIND_DATAA outA) {
    WIN32_FIND_DATAW fdw{};
    BOOL ok = g_FindNextFileW(h, &fdw);
    if (!ok) return ok;
    if (outA) {
        ApplyRandomDateTimes(&fdw);

        memset(outA, 0, sizeof(*outA));
        outA->dwFileAttributes = fdw.dwFileAttributes;
        outA->ftCreationTime = fdw.ftCreationTime;
        outA->ftLastAccessTime = fdw.ftLastAccessTime;
        outA->ftLastWriteTime = fdw.ftLastWriteTime;
        outA->nFileSizeHigh = fdw.nFileSizeHigh;
        outA->nFileSizeLow = fdw.nFileSizeLow;
        strncpy_s(outA->cFileName, W2A_(fdw.cFileName).c_str(), _TRUNCATE);
        strncpy_s(outA->cAlternateFileName, W2A_(fdw.cAlternateFileName).c_str(), _TRUNCATE);
    }
    return TRUE;
}

HANDLE WINAPI DetourCreateFileW(LPCWSTR name, DWORD access, DWORD share,
    LPSECURITY_ATTRIBUTES sa, DWORD disp, DWORD flags, HANDLE tmpl)
{
    if (!IsUnderAnyAllowed(name)) { SetLastError(ERROR_ACCESS_DENIED); return INVALID_HANDLE_VALUE; }
    return g_CreateFileW(name, access, share, sa, disp, flags, tmpl);
}

HANDLE WINAPI DetourCreateFileA(LPCSTR name, DWORD access, DWORD share,
    LPSECURITY_ATTRIBUTES sa, DWORD disp, DWORD flags, HANDLE tmpl)
{
    std::wstring w = A2W_(name);
    if (!IsUnderAnyAllowed(w.c_str())) { SetLastError(ERROR_ACCESS_DENIED); return INVALID_HANDLE_VALUE; }
    return g_CreateFileA(name, access, share, sa, disp, flags, tmpl);
}

struct RegAllow { HKEY hive; const wchar_t* prefix; };
static const RegAllow kRegAllowList[] = {
    { HKEY_CURRENT_USER, L"Software\\Facepunch Studios LTD\\Rust" },
    { HKEY_CURRENT_USER, L"Software\\Facepunch Studios LTD" },
};

static bool RegReadAllowed(HKEY h, LPCWSTR sub, REGSAM sam) {
    if (!sub) return false;
    if ((sam & (KEY_WRITE | WRITE_OWNER | WRITE_DAC | DELETE)) != 0) return false;
    for (auto& a : kRegAllowList) {
        if (h == a.hive) {
            size_t n = wcslen(a.prefix);
            if (_wcsnicmp(sub, a.prefix, (unsigned)n) == 0 && (sub[n] == L'\0' || sub[n] == L'\\')) return true;
        }
    }
    return false;
}

LSTATUS WINAPI DetourRegOpenKeyExW(HKEY h, LPCWSTR sub, DWORD opt, REGSAM sam, PHKEY phk)
{
    if (RegReadAllowed(h, sub, sam)) return g_RegOpenKeyExW(h, sub, opt, sam, phk);
    if (phk) *phk = nullptr; SetLastError(ERROR_ACCESS_DENIED); return ERROR_ACCESS_DENIED;
}

LSTATUS WINAPI DetourRegOpenKeyExA(HKEY h, LPCSTR subA, DWORD opt, REGSAM sam, PHKEY phk)
{
    std::wstring subW = AnsiToWide(subA);
    if (RegReadAllowed(h, subW.c_str(), sam)) return g_RegOpenKeyExA(h, subA, opt, sam, phk);
    if (phk) *phk = nullptr; SetLastError(ERROR_ACCESS_DENIED); return ERROR_ACCESS_DENIED;
}

static bool RegWriteAllowed(HKEY h, LPCWSTR sub) {
    if (!sub) return false;
    for (auto& a : kRegAllowList) {
        if (h == a.hive) {
            size_t n = wcslen(a.prefix);
            if (_wcsnicmp(sub, a.prefix, (unsigned)n) == 0 && (sub[n] == L'\0' || sub[n] == L'\\')) return true;
        }
    }
    return false;
}

LSTATUS WINAPI DetourRegCreateKeyExW(HKEY h, LPCWSTR sub, DWORD r, LPWSTR cls, DWORD opt, REGSAM sam, LPSECURITY_ATTRIBUTES sa, PHKEY phk, LPDWORD disp)
{
    if (RegWriteAllowed(h, sub)) return g_RegCreateKeyExW(h, sub, r, cls, opt, sam, sa, phk, disp);
    if (phk) *phk = nullptr; if (disp) *disp = 0; SetLastError(ERROR_ACCESS_DENIED); return ERROR_ACCESS_DENIED;
}

LSTATUS WINAPI DetourRegCreateKeyExA(HKEY h, LPCSTR subA, DWORD r, LPSTR cls, DWORD opt, REGSAM sam, LPSECURITY_ATTRIBUTES sa, PHKEY phk, LPDWORD disp)
{
    std::wstring subW = AnsiToWide(subA);
    if (RegWriteAllowed(h, subW.c_str())) return g_RegCreateKeyExA(h, subA, r, cls, opt, sam, sa, phk, disp);
    if (phk) *phk = nullptr; if (disp) *disp = 0; SetLastError(ERROR_ACCESS_DENIED); return ERROR_ACCESS_DENIED;
}

static UINT32 DeriveSerial(UINT32 orig) {
    EnsureSeed();
    UINT32 x = orig ? orig : 0x6D5A56F9u;
    x ^= g_seed; x = mix32(x);
    if (x == 0 || x == orig) x ^= 0x5A5A5A5Au;
    return x;
}

static void MakeVolNameW(UINT32 s, LPWSTR buf, DWORD cch) {
    if (!buf || !cch) return;
    wchar_t t[32];
    _snwprintf_s(t, _TRUNCATE, L"VOL-%08X", (unsigned)s);
    wcsncpy_s(buf, cch, t, _TRUNCATE);
}

static void MakeVolNameA(UINT32 s, LPSTR buf, DWORD cch) {
    if (!buf || !cch) return;
    char t[32];
    _snprintf_s(t, _TRUNCATE, "VOL-%08X", (unsigned)s);
    strncpy_s(buf, cch, t, _TRUNCATE);
}

BOOL WINAPI DetourGetVolumeInformationW(LPCWSTR root, LPWSTR volName, DWORD volNameSize,
    LPDWORD serial, LPDWORD maxCompLen, LPDWORD fsFlags, LPWSTR fsName, DWORD fsNameSize)
{
    DWORD origSerial = 0;
    BOOL ok = g_OrigGVIW(root, volName, volNameSize, serial ? &origSerial : nullptr, maxCompLen, fsFlags, fsName, fsNameSize);
    if (!ok) return ok;
    UINT32 fake = DeriveSerial(origSerial);
    if (serial) *serial = fake;
    if (volName && volNameSize) MakeVolNameW(fake, volName, volNameSize);
    return TRUE;
}

BOOL WINAPI DetourGetVolumeInformationA(LPCSTR root, LPSTR volName, DWORD volNameSize,
    LPDWORD serial, LPDWORD maxCompLen, LPDWORD fsFlags, LPSTR fsName, DWORD fsNameSize)
{
    DWORD origSerial = 0;
    BOOL ok = g_OrigGVIA(root, volName, volNameSize, serial ? &origSerial : nullptr, maxCompLen, fsFlags, fsName, fsNameSize);
    if (!ok) return ok;
    UINT32 fake = DeriveSerial(origSerial);
    if (serial) *serial = fake;
    if (volName && volNameSize) MakeVolNameA(fake, volName, volNameSize);
    return TRUE;
}

BOOL WINAPI DetourGetVolumeInformationByHandleW(HANDLE h, LPWSTR volName, DWORD volNameSize,
    LPDWORD serial, LPDWORD maxCompLen, LPDWORD fsFlags, LPWSTR fsName, DWORD fsNameSize)
{
    DWORD origSerial = 0;
    BOOL ok = g_OrigGVIByHW(h, volName, volNameSize, serial ? &origSerial : nullptr, maxCompLen, fsFlags, fsName, fsNameSize);
    if (!ok) return ok;
    UINT32 fake = DeriveSerial(origSerial);
    if (serial) *serial = fake;
    if (volName && volNameSize) MakeVolNameW(fake, volName, volNameSize);
    return TRUE;
}

static UINT8 macByte(UINT8 b, UINT32 n) {
    UINT32 x = mix32((b ? b : (UINT8)(n * 13)) ^ (g_seed + n * 0x45D9F3Bu));
    return (UINT8)(x & 0xFF);
}

static std::string MakeFakeAdapterName(UINT32 index) {
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ (index * 0x12345678u));
    char buf[32];
    _snprintf_s(buf, _TRUNCATE, "Adapter_%08X", x);
    return std::string(buf);
}

static std::string MakeFakeDescription(UINT32 index) {
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ (index * 0x87654321u));
    const char* vendors[] = { "Intel", "Realtek", "Broadcom", "Qualcomm", "Marvell" };
    const char* types[] = { "Ethernet", "Wireless", "Gigabit", "FastEthernet" };
    char buf[128];
    _snprintf_s(buf, _TRUNCATE, "%s %s Network Adapter #%d",
        vendors[x % 5], types[(x >> 8) % 4], (x >> 16) % 99 + 1);
    return std::string(buf);
}

static void MakeFakeIP(char* ipStr, UINT32 base) {
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ base);
    _snprintf_s(ipStr, 16, _TRUNCATE, "192.168.%d.%d",
        (x >> 8) % 254 + 1, (x >> 16) % 254 + 1);
}

ULONG WINAPI DetourGetAdaptersInfo(PIP_ADAPTER_INFO pInfo, PULONG pLen) {
    ULONG r = g_OrigGAI(pInfo, pLen);
    if (r != ERROR_SUCCESS || !pInfo) return r;
    EnsureSeed();

    UINT32 adapterIndex = 0;
    for (PIP_ADAPTER_INFO p = pInfo; p; p = p->Next, adapterIndex++) {
        BYTE origMAC[MAX_ADAPTER_ADDRESS_LENGTH] = {};
        memcpy(origMAC, p->Address, p->AddressLength);
        for (UINT i = 0; i < p->AddressLength && i < MAX_ADAPTER_ADDRESS_LENGTH; ++i) {
            p->Address[i] = macByte(origMAC[i], i);
        }
        if (p->AddressLength == 0 || p->AddressLength > 6) p->AddressLength = 6;

        std::string fakeName = MakeFakeAdapterName(adapterIndex);
        strncpy_s(p->AdapterName, sizeof(p->AdapterName), fakeName.c_str(), _TRUNCATE);

        std::string fakeDesc = MakeFakeDescription(adapterIndex);
        strncpy_s(p->Description, sizeof(p->Description), fakeDesc.c_str(), _TRUNCATE);

        UINT32 indexSeed = mix32(g_seed ^ (adapterIndex * 0xABCDEF00u));
        p->Index = (indexSeed % 1000) + 1;
        p->ComboIndex = p->Index + 100;

        p->Type = 6;

        if (p->IpAddressList.IpAddress.String[0] != '\0') {
            MakeFakeIP(p->IpAddressList.IpAddress.String, indexSeed);
            MakeFakeIP(p->IpAddressList.IpMask.String, indexSeed ^ 0x12345678u);
        }

        if (p->GatewayList.IpAddress.String[0] != '\0') {
            MakeFakeIP(p->GatewayList.IpAddress.String, indexSeed ^ 0x87654321u);
        }

        if (p->DhcpServer.IpAddress.String[0] != '\0') {
            MakeFakeIP(p->DhcpServer.IpAddress.String, indexSeed ^ 0xFEDCBA98u);
        }

        p->HaveWins = FALSE;
        memset(p->PrimaryWinsServer.IpAddress.String, 0, sizeof(p->PrimaryWinsServer.IpAddress.String));
        memset(p->SecondaryWinsServer.IpAddress.String, 0, sizeof(p->SecondaryWinsServer.IpAddress.String));

        time_t now = time(nullptr);
        p->LeaseObtained = now - (indexSeed % 3600);
        p->LeaseExpires = now + 86400 + (indexSeed % 3600);
    }
    return r;
}

BOOL WINAPI DetourGetWindowDisplayAffinity(HWND hWnd, DWORD* pdwAffinity)
{
    if (pdwAffinity) *pdwAffinity = WDA_NONE;
    SetLastError(ERROR_SUCCESS);
    return TRUE;
}

static std::string MakeFakeDuid() {
    EnsureSeed();
    uint32_t x = g_seed;
    char buf[41]{};
    for (int i = 0; i < 40; i++) {
        x = mix32(x ^ (i * 0x9E3779B9u));
        static const char* hex = "0123456789abcdef";
        buf[i] = hex[(x >> ((i & 3) * 4)) & 0xF];
    }
    return std::string(buf, 40);
}

static Il2CppString* __cdecl Detour_GetDeviceUniqueIdentifier() {
    if (!g_il2cpp_string_new) return nullptr;
    auto s = MakeFakeDuid();
    return g_il2cpp_string_new(s.c_str());
}

static std::string MakeFakeProcessorType() {
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ 0x50524F43u);

    const char* vendors[] = { "Intel", "AMD", "Intel", "AMD" };
    const char* models[] = {
        "Core i3", "Core i5", "Core i7", "Core i9",
        "Ryzen 3", "Ryzen 5", "Ryzen 7", "Ryzen 9",
        "Xeon E3", "Xeon E5", "EPYC 7003", "Threadripper"
    };
    const char* suffixes[] = {
        "2100", "3300X", "4790K", "5600X", "7700K", "8400", "9700K", "10400F",
        "11700K", "12400F", "13600K", "5800X", "5950X", "3600", "3700X", "5900X"
    };

    char buf[128];
    _snprintf_s(buf, _TRUNCATE, "%s %s-%s @ %.1fGHz",
        vendors[x % 4],
        models[x % 12],
        suffixes[(x >> 4) % 16],
        2.1f + ((x >> 8) % 32) * 0.1f);
    return std::string(buf);
}

static Il2CppString* __cdecl Detour_GetProcessorType() {
    if (!g_il2cpp_string_new) return nullptr;
    auto s = MakeFakeProcessorType();
    return g_il2cpp_string_new(s.c_str());
}

static int __cdecl Detour_GetProcessorFrequencyMHz() {
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ 0x46524551u);
    return 2100 + (x % 3000);
}

static int __cdecl Detour_GetProcessorCount() {
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ 0x434F5245u);
    const int cores[] = { 2, 4, 6, 8, 12, 16, 20, 24, 32 };
    return cores[x % 9];
}

static int __cdecl Detour_GetPhysicalMemoryMB() {
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ 0x52414D21u);
    const int ramSizes[] = { 4, 8, 12, 16, 24, 32, 48, 64, 96, 128 };
    return ramSizes[x % 10] * 1024;
}

static Il2CppString* __cdecl Detour_GetDeviceName() {
    if (!g_il2cpp_string_new) return nullptr;
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ 0x4E414D45u);
    char buf[32];
    _snprintf_s(buf, _TRUNCATE, "DESKTOP-PC%08X", x);
    return g_il2cpp_string_new(buf);
}

static Il2CppString* __cdecl Detour_GetDeviceModel() {
    if (!g_il2cpp_string_new) return nullptr;
    const char* models[] = {
        "System Product Name", "OptiPlex 7090", "ThinkPad T14", "Custom Build",
        "Precision 5820", "EliteDesk 800", "Inspiron 3880", "Vostro 3681",
        "ProDesk 400", "ThinkCentre M920", "Aspire TC-895", "Pavilion TP01"
    };
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ 0x4D4F4445u);
    return g_il2cpp_string_new(models[x % 12]);
}

static int __cdecl Detour_GetDeviceType() {
    return 0;
}

static int __cdecl Detour_GetGraphicsMemorySize() {
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ 0x5652414Du);
    const int vramSizes[] = { 2, 4, 6, 8, 10, 12, 16, 24 };
    return vramSizes[x % 8] * 1024;
}

static Il2CppString* __cdecl Detour_GetGraphicsDeviceName() {
    if (!g_il2cpp_string_new) return nullptr;
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ 0x47505521u);
    const char* gpus[] = {
        "NVIDIA GeForce GTX 1650", "NVIDIA GeForce GTX 1660", "NVIDIA GeForce GTX 1660 Ti",
        "NVIDIA GeForce RTX 3060", "NVIDIA GeForce RTX 3070", "NVIDIA GeForce RTX 3080",
        "NVIDIA GeForce RTX 4060", "NVIDIA GeForce RTX 4070", "NVIDIA GeForce RTX 4080",
        "AMD Radeon RX 6600", "AMD Radeon RX 6700 XT", "AMD Radeon RX 6800 XT",
        "AMD Radeon RX 7600", "AMD Radeon RX 7700 XT", "AMD Radeon RX 7800 XT",
        "Intel Arc A750", "Intel Arc A770", "NVIDIA Quadro T1000"
    };
    return g_il2cpp_string_new(gpus[x % 18]);
}

static Il2CppString* __cdecl Detour_GetGraphicsDeviceVendor() {
    if (!g_il2cpp_string_new) return nullptr;
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ 0x56454E44u);
    const char* vendors[] = {
        "NVIDIA Corporation", "Advanced Micro Devices, Inc.", "Intel Corporation"
    };
    return g_il2cpp_string_new(vendors[x % 3]);
}

static volatile LONG g_systemInfoHooked = 0;
static bool HookAllSystemInfo() {
    if (InterlockedCompareExchange(&g_systemInfoHooked, 1, 0) != 0) {
        return true;
    }

    HMODULE hGA = GetModuleHandleA("GameAssembly.dll");
    if (!hGA) return false;
    auto resolve = (il2cpp_resolve_icall_t)GetProcAddress(hGA, "il2cpp_resolve_icall");
    g_il2cpp_string_new = (il2cpp_string_new_t)GetProcAddress(hGA, "il2cpp_string_new");
    if (!g_il2cpp_string_new || !resolve) return false;

    struct ICallHook {
        const char* name;
        void* detour;
        void** orig;
    };

    ICallHook hooks[] = {
        {"UnityEngine.SystemInfo::GetDeviceUniqueIdentifier", Detour_GetDeviceUniqueIdentifier, (void**)&g_OrigGetDuid},
        {"UnityEngine.SystemInfo::GetProcessorType", Detour_GetProcessorType, (void**)&g_OrigGetProcessorType},
        {"UnityEngine.SystemInfo::GetProcessorFrequencyMHz", Detour_GetProcessorFrequencyMHz, (void**)&g_OrigGetProcessorFreq},
        {"UnityEngine.SystemInfo::GetProcessorCount", Detour_GetProcessorCount, (void**)&g_OrigGetProcessorCount},
        {"UnityEngine.SystemInfo::GetPhysicalMemoryMB", Detour_GetPhysicalMemoryMB, (void**)&g_OrigGetPhysicalMemory},
        {"UnityEngine.SystemInfo::GetDeviceName", Detour_GetDeviceName, (void**)&g_OrigGetDeviceName},
        {"UnityEngine.SystemInfo::GetDeviceModel", Detour_GetDeviceModel, (void**)&g_OrigGetDeviceModel},
        {"UnityEngine.SystemInfo::GetDeviceType", Detour_GetDeviceType, (void**)&g_OrigGetDeviceType},
        {"UnityEngine.SystemInfo::GetGraphicsMemorySize", Detour_GetGraphicsMemorySize, (void**)&g_OrigGetGraphicsMemory},
        {"UnityEngine.SystemInfo::GetGraphicsDeviceName", Detour_GetGraphicsDeviceName, (void**)&g_OrigGetGraphicsName},
        {"UnityEngine.SystemInfo::GetGraphicsDeviceVendor", Detour_GetGraphicsDeviceVendor, (void**)&g_OrigGetGraphicsVendor},
    };

    int successful = 0;
    for (auto& hook : hooks) {
        void* target = (void*)resolve(hook.name);
        if (!target) continue;
        if (MH_CreateHook(target, hook.detour, hook.orig) == MH_OK &&
            MH_EnableHook(target) == MH_OK) {
            successful++;
        }
    }
    return successful > 0;
}

static inline unsigned BitsInMask() {
#if defined(_WIN64)
    return 64u;
#else
    return 32u;
#endif
}

static inline DWORD_PTR MaskFromCount(DWORD n) {
    unsigned bits = BitsInMask();
    if (n == 0) return 0;
    if (n >= bits) {
        return (DWORD_PTR)(~(DWORD_PTR)0);
    }
    if (bits == 64) return (DWORD_PTR)((n == 64) ? ~0ull : ((1ull << n) - 1ull));
    return (DWORD_PTR)((n == 32) ? 0xFFFFFFFFu : ((1u << n) - 1u));
}

static void ApplySystemInfoFake(LPSYSTEM_INFO si) {
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ 0x434F5245u);
    const DWORD cores[] = { 2, 4, 6, 8, 12, 16, 20, 24, 32 };
    DWORD fakeN = cores[x % 9];

    si->dwNumberOfProcessors = fakeN;
    si->dwActiveProcessorMask = MaskFromCount(fakeN);
}

VOID WINAPI DetourGetSystemInfo(LPSYSTEM_INFO si) {
    g_GetSystemInfo(si);
    ApplySystemInfoFake(si);
}

VOID WINAPI DetourGetNativeSystemInfo(LPSYSTEM_INFO si) {
    g_GetNativeSystemInfo(si);
    ApplySystemInfoFake(si);
}

static void ApplyMemoryFake(LPMEMORYSTATUSEX ms) {
    EnsureSeed();
    UINT32 x = mix32(g_seed ^ 0x52414D21u);
    const int ramSizes[] = { 4, 8, 12, 16, 24, 32, 48, 64, 96, 128 };
    DWORDLONG fakeTotal = (DWORDLONG)ramSizes[x % 10] * 1024 * 1024 * 1024;

    ms->ullTotalPhys = fakeTotal;
    ms->ullAvailPhys = fakeTotal / 2;
    ms->ullTotalVirtual = fakeTotal * 2;
    ms->ullAvailVirtual = fakeTotal;
}

HANDLE WINAPI DetourCreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID) {
    SetLastError(ERROR_ACCESS_DENIED);
    return INVALID_HANDLE_VALUE;
}

BOOL WINAPI DetourThread32First(HANDLE hSnapshot, LPTHREADENTRY32 lpte) {
    SetLastError(ERROR_ACCESS_DENIED);
    return FALSE;
}

BOOL WINAPI DetourThread32Next(HANDLE hSnapshot, LPTHREADENTRY32 lpte) {
    SetLastError(ERROR_ACCESS_DENIED);
    return FALSE;
}

BOOL WINAPI DetourProcess32First(HANDLE hSnapshot, LPPROCESSENTRY32 lppe) {
    SetLastError(ERROR_ACCESS_DENIED);
    return FALSE;
}

BOOL WINAPI DetourProcess32Next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe) {
    SetLastError(ERROR_ACCESS_DENIED);
    return FALSE;
}

BOOL WINAPI DetourModule32First(HANDLE hSnapshot, LPMODULEENTRY32 lpme) {
    SetLastError(ERROR_ACCESS_DENIED);
    return FALSE;
}

BOOL WINAPI DetourModule32Next(HANDLE hSnapshot, LPMODULEENTRY32 lpme) {
    SetLastError(ERROR_ACCESS_DENIED);
    return FALSE;
}
BOOL WINAPI DetourGetModuleInformation(HANDLE hProcess, HMODULE hModule, LPMODULEINFO lpmodinfo, DWORD cb) {
    SetLastError(ERROR_ACCESS_DENIED); return FALSE;
}

BOOL WINAPI DetourK32GetModuleInformation(HANDLE hProcess, HMODULE hModule, LPMODULEINFO lpmodinfo, DWORD cb) {
    SetLastError(ERROR_ACCESS_DENIED); return FALSE;
}

DWORD WINAPI DetourGetModuleFileNameExA(HANDLE hProcess, HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
    SetLastError(ERROR_ACCESS_DENIED); return 0;
}

DWORD WINAPI DetourGetModuleFileNameExW(HANDLE hProcess, HMODULE hModule, LPWSTR lpFilename, DWORD nSize) {
    SetLastError(ERROR_ACCESS_DENIED); return 0;
}

DWORD WINAPI DetourGetModuleBaseNameA(HANDLE hProcess, HMODULE hModule, LPSTR lpBaseName, DWORD nSize) {
    SetLastError(ERROR_ACCESS_DENIED); return 0;
}

DWORD WINAPI DetourGetModuleBaseNameW(HANDLE hProcess, HMODULE hModule, LPWSTR lpBaseName, DWORD nSize) {
    SetLastError(ERROR_ACCESS_DENIED); return 0;
}
NTSTATUS NTAPI DetourNtQueryInformationThread(HANDLE ThreadHandle, THREADINFOCLASS ThreadInformationClass,
    PVOID ThreadInformation, ULONG ThreadInformationLength, PULONG ReturnLength) {
    return STATUS_ACCESS_DENIED;
}

BOOL WINAPI DetourGlobalMemoryStatusEx(LPMEMORYSTATUSEX lpBuffer) {
    if (!lpBuffer || lpBuffer->dwLength < sizeof(MEMORYSTATUSEX)) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    BOOL result = g_GlobalMemoryStatusEx(lpBuffer);
    if (result) {
        ApplyMemoryFake(lpBuffer);
    }
    return result;
}
SIZE_T WINAPI DetourVirtualQueryEx(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
    SetLastError(ERROR_ACCESS_DENIED);
    return 0;
}
BOOL WINAPI DetourEnumProcessModules(HANDLE hProcess, HMODULE* lphModule, DWORD cb, LPDWORD lpcbNeeded) {
    if (lpcbNeeded) *lpcbNeeded = 0;
    SetLastError(ERROR_ACCESS_DENIED);
    return FALSE;
}

BOOL WINAPI DetourEnumProcessModulesEx(HANDLE hProcess, HMODULE* lphModule, DWORD cb, LPDWORD lpcbNeeded, DWORD dwFilterFlag) {
    if (lpcbNeeded) *lpcbNeeded = 0;
    SetLastError(ERROR_ACCESS_DENIED);
    return FALSE;
}
using ConsoleSystemSendToServer_t = void(__cdecl*)(Il2CppString* command);
static ConsoleSystemSendToServer_t g_OrigConsoleSystemSendToServer = nullptr;

static std::string Il2CppStringToStd(Il2CppString* str) {
    if (!str) return "[NULL]";

    std::wstring wstr(str->start_char, str->length);

    int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string result(len - 1, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &result[0], len, nullptr, nullptr);

    return result;
}


void __cdecl Detour_ProcessKill() {}

void __cdecl Detour_EnvironmentFailFast(void* message) {}

static bool HookSecurityExceptions() {
    HMODULE hGA = GetModuleHandleA("GameAssembly.dll");
    if (!hGA) return false;

    auto resolve = (il2cpp_resolve_icall_t)GetProcAddress(hGA, "il2cpp_resolve_icall");
    if (!resolve) return false;

    void* securityExceptionCtor = (void*)resolve("System.Security.SecurityException::.ctor");
    if (securityExceptionCtor) {
        MH_CreateHook(securityExceptionCtor, Detour_ProcessKill, nullptr);
        MH_EnableHook(securityExceptionCtor);
        LogW(L"Blocked SecurityException constructor");
        return true;
    }

    return false;
}

typedef void* (__cdecl* StackTraceGetFrames_t)(void*);
static StackTraceGetFrames_t g_StackTraceGetFrames = nullptr;

void* __cdecl Detour_StackTraceGetFrames(void* stackTrace) {
    return nullptr;
}

static bool HookStackTraceAnalysis() {
    HMODULE hGA = GetModuleHandleA("GameAssembly.dll");
    if (!hGA) return false;

    auto resolve = (il2cpp_resolve_icall_t)GetProcAddress(hGA, "il2cpp_resolve_icall");
    if (!resolve) return false;

    void* target = (void*)resolve("System.Diagnostics.StackTrace::GetFrames");
    if (target) {
        MH_CreateHook(target, Detour_StackTraceGetFrames, (LPVOID*)&g_StackTraceGetFrames);
        MH_EnableHook(target);
        LogW(L"Hooked StackTrace.GetFrames()");
        return true;
    }

    return false;
}



static bool InstallBypass() {
    if (MH_Initialize() != MH_OK) return false;

    BuildAllowlistPaths();

    MH_CreateHookApi(L"ntdll", "NtQueryInformationThread", DetourNtQueryInformationThread, (LPVOID*)&g_NtQueryInformationThread);

    MH_CreateHookApi(L"psapi", "EnumProcessModules", DetourEnumProcessModules, (LPVOID*)&g_EnumProcessModules);
    MH_CreateHookApi(L"psapi", "EnumProcessModulesEx", DetourEnumProcessModulesEx, (LPVOID*)&g_EnumProcessModulesEx);

    MH_CreateHookApi(L"kernel32", "VirtualQueryEx", DetourVirtualQueryEx, (LPVOID*)&g_VirtualQueryEx);

    MH_CreateHookApi(L"psapi", "GetModuleInformation", DetourGetModuleInformation, (LPVOID*)&g_GetModuleInformation);
    MH_CreateHookApi(L"kernel32", "K32GetModuleInformation", DetourK32GetModuleInformation, (LPVOID*)&g_K32GetModuleInformation);
    MH_CreateHookApi(L"psapi", "GetModuleFileNameExA", DetourGetModuleFileNameExA, (LPVOID*)&g_GetModuleFileNameExA);
    MH_CreateHookApi(L"psapi", "GetModuleFileNameExW", DetourGetModuleFileNameExW, (LPVOID*)&g_GetModuleFileNameExW);
    MH_CreateHookApi(L"psapi", "GetModuleBaseNameA", DetourGetModuleBaseNameA, (LPVOID*)&g_GetModuleBaseNameA);
    MH_CreateHookApi(L"psapi", "GetModuleBaseNameW", DetourGetModuleBaseNameW, (LPVOID*)&g_GetModuleBaseNameW);

    MH_CreateHookApi(L"kernel32", "CreateToolhelp32Snapshot", DetourCreateToolhelp32Snapshot, (LPVOID*)&g_CreateToolhelp32Snapshot);
    MH_CreateHookApi(L"kernel32", "Thread32First", DetourThread32First, (LPVOID*)&g_Thread32First);
    MH_CreateHookApi(L"kernel32", "Thread32Next", DetourThread32Next, (LPVOID*)&g_Thread32Next);
    MH_CreateHookApi(L"kernel32", "Process32First", DetourProcess32First, (LPVOID*)&g_Process32First);
    MH_CreateHookApi(L"kernel32", "Process32Next", DetourProcess32Next, (LPVOID*)&g_Process32Next);
    MH_CreateHookApi(L"kernel32", "Module32First", DetourModule32First, (LPVOID*)&g_Module32First);
    MH_CreateHookApi(L"kernel32", "Module32Next", DetourModule32Next, (LPVOID*)&g_Module32Next);

    MH_CreateHookApi(L"kernel32", "GlobalMemoryStatusEx", DetourGlobalMemoryStatusEx, (LPVOID*)&g_GlobalMemoryStatusEx);

    MH_CreateHookApi(L"advapi32", "RegOpenKeyExW", DetourRegOpenKeyExW, (LPVOID*)&g_RegOpenKeyExW);
    MH_CreateHookApi(L"advapi32", "RegOpenKeyExA", DetourRegOpenKeyExA, (LPVOID*)&g_RegOpenKeyExA);
    MH_CreateHookApi(L"advapi32", "RegCreateKeyExW", DetourRegCreateKeyExW, (LPVOID*)&g_RegCreateKeyExW);
    MH_CreateHookApi(L"advapi32", "RegCreateKeyExA", DetourRegCreateKeyExA, (LPVOID*)&g_RegCreateKeyExA);

    MH_CreateHookApi(L"kernel32", "CreateFileW", DetourCreateFileW, (LPVOID*)&g_CreateFileW);
    MH_CreateHookApi(L"kernel32", "CreateFileA", DetourCreateFileA, (LPVOID*)&g_CreateFileA);
    MH_CreateHookApi(L"kernel32", "GetFileAttributesExW", DetourGetFileAttributesExW, (LPVOID*)&g_GetFileAttributesExW);
    MH_CreateHookApi(L"kernel32", "GetFileAttributesExA", DetourGetFileAttributesExA, (LPVOID*)&g_GetFileAttributesExA);
    MH_CreateHookApi(L"kernel32", "FindFirstFileW", DetourFindFirstFileW, (LPVOID*)&g_FindFirstFileW);
    MH_CreateHookApi(L"kernel32", "FindFirstFileA", DetourFindFirstFileA, (LPVOID*)&g_FindFirstFileA);
    MH_CreateHookApi(L"kernel32", "FindNextFileW", DetourFindNextFileW, (LPVOID*)&g_FindNextFileW);
    MH_CreateHookApi(L"kernel32", "FindNextFileA", DetourFindNextFileA, (LPVOID*)&g_FindNextFileA);
    MH_CreateHookApi(L"kernel32", "GetVolumeInformationW", DetourGetVolumeInformationW, (LPVOID*)&g_OrigGVIW);
    MH_CreateHookApi(L"kernel32", "GetVolumeInformationA", DetourGetVolumeInformationA, (LPVOID*)&g_OrigGVIA);
    MH_CreateHookApi(L"kernel32", "GetVolumeInformationByHandleW", DetourGetVolumeInformationByHandleW, (LPVOID*)&g_OrigGVIByHW);
    MH_CreateHookApi(L"iphlpapi", "GetAdaptersInfo", DetourGetAdaptersInfo, (LPVOID*)&g_OrigGAI);

    MH_CreateHookApi(L"kernel32", "GetSystemInfo", DetourGetSystemInfo, (LPVOID*)&g_GetSystemInfo);
    MH_CreateHookApi(L"kernel32", "GetNativeSystemInfo", DetourGetNativeSystemInfo, (LPVOID*)&g_GetNativeSystemInfo);

    MH_CreateHookApi(L"user32", "GetWindowDisplayAffinity", DetourGetWindowDisplayAffinity, (LPVOID*)&g_OrigGetWDA);

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) return false;

    Sleep(1000);
    HookAllSystemInfo();
    HookStackTraceAnalysis();
    HookSecurityExceptions();
    return true;
}

static void RemoveAllHooks() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}

