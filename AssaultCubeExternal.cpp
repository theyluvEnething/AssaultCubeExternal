#include <iostream>
#include "stdafx.h"
#include "proc.h"
#include <Windows.h>
#include <vector>

int main()
{
    

    // testing
    // *[ac_client.exe+17E0A8] + 140 == ammo value


    std::cout << "Assault Cube External!\n";
    //  Get procid
    DWORD procId = GetProcId(L"ac_client.exe");
    std::cout << procId << std::endl;
       
    // get module base adress
    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

    // get handle to right process
    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    
    // Resolve base addres to pointer chain
    std::cout << "ModuleBase: " << moduleBase << std::endl;
    uintptr_t dynamicPtrBaseAddress = moduleBase + 0x17E0A8;
    std::cout << "DynamicBaseAddress = " << "0x" << std::hex << dynamicPtrBaseAddress << std::endl;

    // Resolve right pointer
    std::vector<unsigned int> ammoOffset = {0x140};
    uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddress, ammoOffset);
    std::cout << "ammoAddr = " << "0x" << std::hex << ammoAddr << std::endl;


     // Read and Write to pointer value
    int ammoValue = 0;
    ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
    std::cout << "Current Ammo = " << std::dec << ammoValue << std::endl;

    int newAmmo = 1337;
    WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

    ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
    std::cout << "New Ammo = " << std::dec << ammoValue << std::endl;

    getchar();

    return 0;
}
