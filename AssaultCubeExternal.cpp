#include <iostream>
#include "stdafx.h"
#include "proc.h"
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include <stdlib.h>
#include <tchar.h>


int main()
{
    // testing
    // *[ac_client.exe+17E0A8] + 140 == ammo value


    std::cout << "Assault Cube External!\n";

    HWND hwnd_AC = FindWindowA(NULL, "AssaultCube"); // get handle to window

    if (hwnd_AC != FALSE);

    DWORD pid = NULL;
    GetWindowThreadProcessId(hwnd_AC, &pid);
    HANDLE pHandle = NULL;
    pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (pHandle == INVALID_HANDLE_VALUE || pHandle == NULL);

    wchar_t gameModule[] = L"ac_client.exe";
    DWORD gameBaseAddress = GetModuleBaseAddress(gameModule, pid);

    DWORD ammoAddr = 0x195404;
    std::vector<DWORD> ammoOffsets{ 0x140 };
    DWORD ammoPtrAdress = GetPointerAddress(hwnd_AC, gameBaseAddress, ammoAddr, ammoOffsets);

    //write memory
    while (true) {
        int ammo = 1337;
        WriteProcessMemory(pHandle, (LPVOID*)(ammoPtrAdress), &ammo, 4, 0);
    }

    ////  Get procid
    //DWORD procId = GetProcId(L"ac_client.exe");
    //std::cout << procId << std::endl;
    //   
    //// get module base adress
    //uintptr_t moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

    //// get handle to right process
    //HANDLE hProcess = 0;
    //hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    //
    //// Resolve base addres to pointer chain
    //std::cout << "ModuleBase: " << moduleBase << " | 0x" << std::hex << moduleBase << std::endl;

    //// Resolve right pointer
    //DWORD playerAddress = 0x195404;
    //std::vector<unsigned int> ammoOffsets = { 0xEC };
    //uintptr_t healthAddr = FindDMAAddy(hProcess, moduleBase, ammoOffsets);
    //std::cout << "healthAddr = " << healthAddr << " | 0x" << std::hex << healthAddr << std::endl;





    getchar();

    return 0;
}
