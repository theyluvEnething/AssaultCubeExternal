#include <iostream>
#include "stdafx.h"
#include "proc.h"
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include <stdlib.h>
#include <tchar.h>

#include "memory.h"


int main(void*)
{
    // *[ac_client.exe+17E0A8] + 140 == ammo value
    std::cout << "Assault Cube External!\n";

    // resolve window handle
    HWND hwnd = FindWindowA(NULL, "AssaultCube"); // get handle to window
    if (hwnd == 0) {
        std::cout << "INVALID HWND" << std::endl;
        return 1;
    }


    // resolve pid
    DWORD pid = NULL;
    GetWindowThreadProcessId(hwnd, &pid);

    // resolve process handle
    HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (pHandle == INVALID_HANDLE_VALUE || pHandle == NULL) {
        std::cout << "INVALID HANDLE" << std::endl;
        return 1;
    }


    // module base
    wchar_t gameModule[] = L"ac_client.exe";
    uintptr_t gameBaseAddress = GetModuleBaseAddress(gameModule, pid);
    std::cout << "GameBaseAddress: " << gameBaseAddress << " | 0x" << std::hex << gameBaseAddress << std::endl;

    memory::setpHandle(&pHandle);
    memory::setBaseAddress(gameBaseAddress);
    memory::setHWDN(&hwnd);

    DWORD ammoAddr = 0x17E0A8;
    std::vector<DWORD> ammoOffsets{ 0x368, 0x14, 0x0 };


    int ammo = -1;
    memory::read(ammoAddr, ammoOffsets, &ammo, sizeof(ammo));
    std::cout << "Current Ammo: " << std::dec << ammo << std::endl;
   

    DWORD recoild= 0x17E0A8;
    std::vector<DWORD> recoilOffsets01{ 0x364, 0xC, 0x5E };
    std::vector<DWORD> recoilOffsets02{ 0x364, 0xC, 0x60 };
    uint16_t newRecoil = 0;
    memory::write(recoild, recoilOffsets01, &newRecoil, sizeof(newRecoil));
    memory::write(recoild, recoilOffsets02, &newRecoil, sizeof(newRecoil));


    while (true) {
        ammo = 1337;
        memory::write(ammoAddr, ammoOffsets, &ammo, sizeof(ammo));
    }


    //// get handle to right process
    //HANDLE hProcess = 0;
    //hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    //
    //// Resolve base addres to pointer chain

    //// Resolve right pointer
    //DWORD playerAddress = 0x195404;
    //std::vector<unsigned int> ammoOffsets = { 0xEC };
    //uintptr_t healthAddr = FindDMAAddy(hProcess, moduleBase, ammoOffsets);
    //std::cout << "healthAddr = " << healthAddr << " | 0x" << std::hex << healthAddr << std::endl;

    //int ammoValue = 0;
    //ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
    //std::cout << "Current Ammo = " << std::dec << ammoValue << std::endl;

    //int newAmmo = 1337;
    //WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

    //ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
    //std::cout << "New Ammo = " << std::dec << ammoValue << std::endl;

    getchar();


    return 0;
}
