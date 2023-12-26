#include "proc.h"
#include "../stdafx.h"
#include <wchar.h>
#include <vector>
#include <Windows.h>
#include <iostream>

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

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {

	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); i++) {
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}


DWORD GetModuleBaseAddress(wchar_t* lpszModuleName, DWORD pid) {
	DWORD dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid); // make snapshot of all modules within process
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
	DWORD pid = NULL; // Game process ID
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE pHandle = NULL;
	pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (pHandle == INVALID_HANDLE_VALUE || pHandle == NULL) return -1;

	DWORD offset_null = NULL;
	ReadProcessMemory(pHandle, (LPVOID*)(gameBaseAddr + address), &offset_null, sizeof(offset_null), 0);
	std::cout << "First: " << offset_null << std::endl;
	DWORD pointeraddress = offset_null; // the address we need
	for (int i = 0; i < offsets.size() - 1; i++) // we dont want to change the last offset value so we do -1
	{
		ReadProcessMemory(pHandle, (LPVOID*)(pointeraddress + offsets[i]), &pointeraddress, sizeof(pointeraddress), 0);
		std::cout << "Continue: " << pointeraddress << std::endl;
	}
	return pointeraddress += offsets.at(offsets.size() - 1); // adding the last offset
}