#include <iostream>
#include <iomanip>

#include "cheat.h"
#include "../memory/memory.h"
#include "../data/offsets.h"
#include "../utils/utils.h"
#include "../proc/proc.h"
#include "../utils/math.h"
#include "../gui/window.h"

entity cheat::player;

int cheat::hook() {
    std::cout << "Hooking cheat..." << std::endl;


    HWND hwnd = FindWindowA(NULL, "AssaultCube"); // get handle to window
    if (hwnd == 0) {
        std::cout << "INVALID HWND - Open Assault Cube" << std::endl;
        exit(1);
        return 1;
    }

    // resolve pid
    DWORD pid = NULL;
    GetWindowThreadProcessId(hwnd, &pid);

    // resolve process handle
    HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (pHandle == INVALID_HANDLE_VALUE || pHandle == NULL) {
        std::cout << "INVALID HANDLE" << std::endl; 
        exit(1);
        return 1;
    }

    // module base
    wchar_t gameModule[] = L"ac_client.exe";
    uintptr_t gameBaseAddress = GetModuleBaseAddress(gameModule, pid);
    std::cout << "GameBaseAddress: " << gameBaseAddress << " | 0x" << std::hex << gameBaseAddress << std::endl;

    memory::setpHandle(&pHandle);
    memory::setBaseAddress(gameBaseAddress);
    memory::setHWDN(&hwnd);

    return 0;
}

int cheat::setup() {
    std::cout << "Assault Cube External!\n";

    memory::read(offset::ammoAddr, offset::ammoOffsets, &cheat::player.ammo, sizeof(cheat::player.ammo));
    std::cout << "Previus Ammo: " << std::dec << cheat::player.ammo << std::endl;

    uint16_t newRecoil = 0;
    memory::write(offset::recoilAddr, offset::recoilOffsets01, &newRecoil, sizeof(newRecoil));
    memory::write(offset::recoilAddr, offset::recoilOffsets02, &newRecoil, sizeof(newRecoil));


    memory::read(offset::localplayer, std::vector<DWORD>{offset::entityHealth}, &cheat::player.health, sizeof(cheat::player.health)); // health
    memory::read(offset::localplayer, std::vector<DWORD>{offset::entityName}, &cheat::player.name, sizeof(cheat::player.name)); // name
    memory::read(offset::localplayer, std::vector<DWORD>{offset::entityPosX}, &cheat::player.pos.x, sizeof(cheat::player.pos.x)); // x
    memory::read(offset::localplayer, std::vector<DWORD>{offset::entityPosY}, &cheat::player.pos.y, sizeof(cheat::player.pos.y)); // y 
    memory::read(offset::localplayer, std::vector<DWORD>{offset::entityPosZ}, &cheat::player.pos.z, sizeof(cheat::player.pos.z)); // z
    memory::read(offset::iViewMatrix, &cheat::player.view_matrix, sizeof(cheat::player.view_matrix));

    cheat::player.print();


    int entityCount = 0;
    // ac_client.exe+18AC0C -> 0058AC0C
    memory::read(0x0058AC0C, &entityCount, sizeof(entityCount));
    std::cout << "Game has " << entityCount << " enemies." << std::endl << std::endl;
    // std::vector<entity> entityArr(entitySize);

    std::cout << "LOCALPLAYER: " << std::left << std::setw(12) << cheat::player.name
        << std::setw(7) << std::right << " (" << cheat::player.health << ") | " << std::setw(4) << std::right
        << "[" << cheat::player.pos.x << ", " << cheat::player.pos.y << ", " << cheat::player.pos.z << "]" << std::endl;

    // loop through entitys
    for (int i = 0; i < entityCount - 1; i++) {
        // entity variables
        int entityHealth = 0;
        char entityName[20] = "";
        vector3 entityPos = { 0, 0, 0 };

        DWORD currEntity = i * offset::entityDistance;



        memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityHealth}, & entityHealth, sizeof(entityHealth)); // health
        memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityName}, & entityName, sizeof(entityName)); // name
        memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityPosX}, & entityPos.x, sizeof(entityPos.x)); // x
        memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityPosY}, & entityPos.y, sizeof(entityPos.y)); // y 
        memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityPosZ}, & entityPos.z, sizeof(entityPos.y)); // z

        //std::cout << i << " - " << std::setw(5) << entityPos.x << " " << entityPos.z << " " << entityPos.y << std::endl;
        std::cout << "ENTITY[" << i << "]: " << std::left << std::setw(15) << entityName
            << std::setw(7) << std::right << " (" << entityHealth << ") | " << std::setw(4) << std::right
            << "[" << entityPos.x << ", " << entityPos.y << ", " << entityPos.z << "]" << std::endl;
    }
	return 0;
}

int cheat::present() {
    // *[ac_client.exe+17E0A8] + 140 == ammo value
    //entity localPlayer = { 0 };
    //memory::read(offset::localplayer, std::vector<DWORD>{offset::entityHealth}, & localPlayer.health, sizeof(localPlayer.health)); // health
    //memory::read(offset::localplayer, std::vector<DWORD>{offset::entityName}, & localPlayer.name, sizeof(localPlayer.name)); // name
    //memory::read(offset::localplayer, std::vector<DWORD>{offset::entityPosX}, & localPlayer.pos.x, sizeof(localPlayer.pos.x)); // x
    //memory::read(offset::localplayer, std::vector<DWORD>{offset::entityPosY}, & localPlayer.pos.y, sizeof(localPlayer.pos.y)); // y 
    //memory::read(offset::localplayer, std::vector<DWORD>{offset::entityPosZ}, & localPlayer.pos.z, sizeof(localPlayer.pos.z)); // z

    //int entitySize = 0;
    //memory::read(offset::entityListLength, &entitySize, sizeof(entitySize));
    //std::cout << "Game has " << entitySize << " enemies." << std::endl << std::endl;
    //// std::vector<entity> entityArr(entitySize);

    //std::cout << "LOCALPLAYER: " << std::left << std::setw(12) << localPlayer.name
    //    << std::setw(7) << std::right << " (" << localPlayer.health << ") | " << std::setw(4) << std::right
    //    << "[" << localPlayer.pos.x << ", " << localPlayer.pos.y << ", " << localPlayer.pos.z << "]" << std::endl;

    //// loop through entitys
    //for (int i = 0; i < entitySize - 1; i++) {
    //    // entity variables
    //    int entityHealth = 0;
    //    char entityName[20] = "";
    //    vector3 entityPos = { 0, 0, 0 };

    //    DWORD currEntity = i * offset::entityDistance;

    //    memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityHealth}, & entityHealth, sizeof(entityHealth)); // health
    //    memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityName}, & entityName, sizeof(entityName)); // name
    //    memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityPosX}, & entityPos.x, sizeof(entityPos.x)); // x
    //    memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityPosY}, & entityPos.y, sizeof(entityPos.y)); // y 
    //    memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityPosZ}, & entityPos.z, sizeof(entityPos.y)); // z

    //    //std::cout << i << " - " << std::setw(5) << entityPos.x << " " << entityPos.z << " " << entityPos.y << std::endl;
    //    std::cout << "ENTITY[" << i << "]: " << std::left << std::setw(15) << entityName
    //        << std::setw(7) << std::right << " (" << entityHealth << ") | " << std::setw(4) << std::right
    //        << "[" << entityPos.x << ", " << entityPos.y << ", " << entityPos.z << "]" << std::endl;
    //}

    int ammo = 1337;
    memory::write(offset::ammoAddr, offset::ammoOffsets, &ammo, sizeof(ammo));



    return 0;
}

void cheat::esp()
{
    memory::read(offset::iViewMatrix, &cheat::player.view_matrix, sizeof(cheat::player.view_matrix));
    //cheat::player.print_angles();
    
    RECT rect = {0};

    struct Screen screen = {
        0,
        0
    };

    memory::read(offset::iGameWidth, &screen.width, sizeof(screen.width));
    memory::read(offset::iGameHeight, &screen.height, sizeof(screen.height));



    int entityCount = 0;
    memory::read(offset::uEntityCount, & entityCount, sizeof(entityCount));

    for (int i = 0; i < entityCount - 1; i++) {
        // entity variables
        int entityHealth = 0;
        char entityName[20] = "";
        vector3 entityPos = { 0, 0, 0 };

        DWORD currEntity = i * offset::entityDistance;

        memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityHealth}, & entityHealth, sizeof(entityHealth)); // health
        memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityName}, & entityName, sizeof(entityName)); // name
        memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityPosX}, & entityPos.x, sizeof(entityPos.x)); // x
        memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityPosY}, & entityPos.y, sizeof(entityPos.y)); // y 
        memory::read(offset::entitylist, std::vector<DWORD>{currEntity, offset::entityPosZ}, & entityPos.z, sizeof(entityPos.y)); // z
    
        v2i coordinates = math::WorldToScreen(entityPos, cheat::player.view_matrix, screen);
        
        if (coordinates.x == -1 && coordinates.y == -1)
            continue;

        std::cout << std::fixed << std::setprecision(2);
        /*
        std::cout << entityName << ": [" << entityPos.x << ", " << entityPos.y << ", " << entityPos.z << "] -> " 
            << "(" << coordinates.x << "/" << coordinates.y << ")"
            << std::endl;
        */
        player.print_angles();

        //std::cout << coordinates.x << " | " << coordinates.y << std::endl;
        window::draw_rectangle(coordinates, vec2i(10, 10), window::BRUSH_RED);
    }

    return;
}
