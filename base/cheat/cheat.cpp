#include <iostream>
#include <iomanip>

#include "cheat.h"
#include "../memory/memory.h"
#include "../data/offsets.h"
#include "../utils/utils.h"
#include "../proc/proc.h"
#include "../utils/math.h"
#include "../gui/window.h"
#include "../data/entity.h"

// general
entity cheat::player;
std::vector<entity> cheat::entityArr;
uint32_t cheat::box_size = 2400;

// cheat var
f32 cheat::FOV = 90;




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
    std::cout << "GameBaseAddress: " << gameBaseAddress << " | 0x" << std::hex << gameBaseAddress << std::dec << std::endl;

    memory::setpHandle(&pHandle);
    memory::setBaseAddress(gameBaseAddress);
    memory::setHWDN(&hwnd);

    return 0;
}

int cheat::setup() {
    std::cout << "Assault Cube External!\n";

    memory::read(offset::iGameWidth, &screen.width, sizeof(screen.width));
    memory::read(offset::iGameHeight, &screen.height, sizeof(screen.height));
    std::cout << "Window Size: " << std::dec << screen.width << " | " << screen.height << std::endl;

    memory::read(offset::ammoAddr, offset::ammoOffsets, &cheat::player.ammo, sizeof(cheat::player.ammo));
    std::cout << "Previus Ammo: " << std::dec << cheat::player.ammo << std::endl;

    uint16_t newRecoil = 0;
    memory::write(offset::recoilAddr, offset::recoilOffsets01, &newRecoil, sizeof(newRecoil));
    memory::write(offset::recoilAddr, offset::recoilOffsets02, &newRecoil, sizeof(newRecoil));




    cheat::updateLocalPlayer();
    cheat::player.print();


    int entityCount = 0;
    memory::read(0x0058AC0C, &entityCount, sizeof(entityCount));
    std::cout << "Game has " << entityCount << " enemies." << std::endl << std::endl;

    std::cout << "LOCALPLAYER: " << std::left << std::setw(12) << cheat::player.name
        << std::setw(7) << std::right << " (" << cheat::player.health << ") | " << std::setw(4) << std::right
        << "[" << cheat::player.pos.x << ", " << cheat::player.pos.y << ", " << cheat::player.pos.z << "]" << std::endl;


    entityArr = cheat::getEntityArr();
    int index = 0;
    for (entity e : entityArr) {
        std::cout << "ENTITY[" << index << "]: " << std::left << std::setw(15) << e.name
            << std::setw(7) << std::right << " (" << e.health << ") | " << std::setw(4) << std::right
            << "[" << e.pos.x << ", " << e.pos.y << ", " << e.pos.z << "]" << std::endl;
        index++;
    }
	return 0;
}

int cheat::present() {
    cheat::updateLocalPlayer();
    entityArr = cheat::getEntityArr();
    
    window::draw_circle(screen.center, FOV, 3, window::BRUSH_CYAN);


    int ammo = 1337;
    memory::write(offset::ammoAddr, offset::ammoOffsets, &ammo, sizeof(ammo));

    return 0;
}

void cheat::esp()
{
    for (entity e : entityArr) {
        v2i coordinates = math::WorldToScreen(e.pos, cheat::player.view_matrix);

        if (coordinates.x == -1 && coordinates.y == -1)
            continue;

        f32 dist = math::distance(e.pos, cheat::player.pos);
        f32 mult = 1 / dist;

        coordinates.y += cheat::box_size * mult * 0.35f;
        window::draw_border_box(coordinates, vec2i((int)(cheat::box_size * mult * 0.35f), (int)(box_size * mult)), 1, window::BRUSH_RED);
        window::draw_line(v2i{ screen.width / 2, screen.height }, coordinates, 1, window::BRUSH_LIGHT_GREEN);
    }

    return;
}

void cheat::aimbot()
{

    // ADD ONLY SHOOTING ON ALIVE PLAYERS


    for (entity e : entityArr) {
        f32 dist = math::distance(e.pos, cheat::player.pos);



        v3 delta = e.pos - cheat::player.pos;

        f32 yaw = atan2f(delta.y, delta.x) * 180 / 3.14f; // Find angle for x direction
        f32 hyp = sqrt(delta.x * delta.x + delta.y * delta.y);   // Find angle for y direction
        f32 pitch = atan2f(delta.z, hyp) * 180 / 3.14f;


        cheat::player.viewangle = {
            yaw + 90,
            pitch
        };


        if (GetAsyncKeyState(VK_CONTROL) && inFOV(e.pos)) { // if control is pressed
            memory::write(offset::iLocalPlayer, std::vector<DWORD>{offset::eViewAngle}, & cheat::player.viewangle, sizeof(cheat::player.viewangle));
        }
    }
}

std::vector<entity> cheat::getEntityArr() {
    std::vector<entity> ent;

    int entityCount = 0;
    memory::read(offset::uEntityCount, &entityCount, sizeof(entityCount));

    for (int i = 0; i < entityCount - 1; i++) {
        entity e;
        DWORD currEntity = i * offset::uEntitySize;

        memory::read(offset::uEntityList, std::vector<DWORD>{currEntity, offset::eHealth}, &e.health, sizeof(e.health));
        memory::read(offset::uEntityList, std::vector<DWORD>{currEntity, offset::eEntityName}, &e.name, sizeof(e.name));
        memory::read(offset::uEntityList, std::vector<DWORD>{currEntity, offset::ePos}, &e.pos, sizeof(e.pos));

        ent.push_back(e);
    }

    return ent;
}

void cheat::updateLocalPlayer() {
    memory::read(offset::iLocalPlayer, std::vector<DWORD>{offset::eEntityName}, & cheat::player.name, sizeof(cheat::player.name)); 
    memory::read(offset::iLocalPlayer, std::vector<DWORD>{offset::eHealth}, & cheat::player.health, sizeof(cheat::player.health));
    memory::read(offset::iLocalPlayer, std::vector<DWORD>{offset::ePos}, & cheat::player.pos, sizeof(cheat::player.pos));
    memory::read(offset::iViewMatrix, &cheat::player.view_matrix, sizeof(cheat::player.view_matrix));
    memory::read(offset::iLocalPlayer, std::vector<DWORD>{offset::eViewAngle}, & cheat::player.viewangle, sizeof(cheat::player.viewangle));
}

bool cheat::inFOV(v3 pos) {
    v2i temp = math::WorldToScreen(pos, cheat::player.view_matrix);
    if (math::distance(v2{(f32)temp.x, (f32)temp.y}, v2{screen.width / 2.0f, screen.height / 2.0f}) < cheat::FOV)
        return true;

    return false;
}