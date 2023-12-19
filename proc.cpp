#include "proc.h"
#include "stdafx.h"
#include <wchar.h>
#include <vector>

DWORD GetProcId(const wchar_t* procName) {
	DWORD procId = 0;
	HANDLE hSnap = (CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {

			do {
				if (!_wcsicmp(procEntry.szExeFile, procName)) {
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));

		}
	}
	CloseHandle(hSnap);
	return procId;
}

//uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName) {
//	uintptr_t modBaseAddress = 0;
//	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
//	if (hSnap != INVALID_HANDLE_VALUE) {
//		
//		MODULEENTRY32 modEntry;
//		modEntry.dwSize = sizeof(modEntry);
//		
//		if (Module32First(hSnap, &modEntry)) {
//			do {
//				if (!_wcsicmp(modEntry.szModule, modName)) {
//					modBaseAddress = (uintptr_t)modEntry.modBaseAddr;
//					break;
//				}
//			} while (Module32Next(hSnap, &modEntry));
//		}
//	}
//	CloseHandle(hSnap);
//	return modBaseAddress;
//}

//uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
//
//	uintptr_t addr = ptr;
//	for (unsigned int i = 0; i < offsets.size(); i++) {
//		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
//		addr += offsets[i];
//	}
//	return addr;
//}


DWORD GetModuleBaseAddress(wchar_t* lpszModuleName, DWORD pID) {
	DWORD dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID); // make snapshot of all modules within process
	MODULEENTRY32 ModuleEntry32 = { 0 };
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry32)) //store first Module in ModuleEntry32
	{
		do {
			if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0) // if Found Module matches Module we look for -> done!
			{
				dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32)); // go through Module entries in Snapshot and store in ModuleEntry32


	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}

DWORD GetPointerAddress(HWND hwnd, DWORD gameBaseAddr, DWORD address, std::vector<DWORD> offsets)
{
	DWORD pID = NULL; // Game process ID
	GetWindowThreadProcessId(hwnd, &pID);
	HANDLE phandle = NULL;
	phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if (phandle == INVALID_HANDLE_VALUE || phandle == NULL);

	DWORD offset_null = NULL;
	ReadProcessMemory(phandle, (LPVOID*)(gameBaseAddr + address), &offset_null, sizeof(offset_null), 0);
	DWORD pointeraddress = offset_null; // the address we need
	for (int i = 0; i < offsets.size() - 1; i++) // we dont want to change the last offset value so we do -1
	{
		ReadProcessMemory(phandle, (LPVOID*)(pointeraddress + offsets.at(i)), &pointeraddress, sizeof(pointeraddress), 0);
	}
	return pointeraddress += offsets.at(offsets.size() - 1); // adding the last offset
}
