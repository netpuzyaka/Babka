#pragma warning(disable : 4530)
#pragma warning(disable : 4244)
#pragma warning(disable : 5040)
#include "includes.h"
#include "Utils/Il2cpp/lazy_importer.hpp"
#pragma comment(lib, "ntdll.lib")
using namespace std;

VOID EraseHeaders(HMODULE hModule)
{
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hModule;
	PIMAGE_NT_HEADERS pNTHeader = (PIMAGE_NT_HEADERS)((PBYTE)pDosHeader + (ULONG)pDosHeader->e_lfanew);

	ULONG OldProtect = NULL;
	ULONG DosImageSize = sizeof(IMAGE_DOS_HEADER);

	if (VirtualProtectEx((HANDLE)-1, pDosHeader, DosImageSize, PAGE_READWRITE, &OldProtect))
	{
		for (ULONG i = 0; i < DosImageSize; i++)
			*(BYTE*)((BYTE*)pDosHeader + i) = 0;
	}

	ULONG NtImageSize = sizeof(IMAGE_NT_HEADERS);

	if (pDosHeader && VirtualProtectEx((HANDLE)-1, pDosHeader, NtImageSize, PAGE_READWRITE, &OldProtect))
	{
		for (ULONG i = 0; i < NtImageSize; i++)
			*(BYTE*)((BYTE*)pDosHeader + i) = 0;
	}
}
void ETONEPASTA()
{
	il2cpp::init();
	Start();
	hk__();

}

#include <iostream>
#include <Windows.h>
#include <tchar.h>

bool DllMain(HMODULE hMod, std::uint32_t call_reason, void*) {
	if (call_reason != DLL_PROCESS_ATTACH)
		return false;

	const auto handle = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ETONEPASTA), hMod, 0, nullptr);

	if (handle != NULL)
		CloseHandle(handle);

	return true;
}