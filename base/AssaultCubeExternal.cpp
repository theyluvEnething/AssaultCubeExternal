#include <iostream>
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include <stdlib.h>
#include <tchar.h>
#include <iomanip>
#include "stdafx.h"


#include "proc/proc.h"
#include "data/offsets.h"
#include "utils/utils.h"
#include "memory/memory.h"

#include "gui/window.h"
#include "cheat/cheat.h"
#include "utils/utils.h"

void init();

int main(void*)
{
    init();

    cheat::hook();
    cheat::setup();

    //HWND hwnd = memory::getHWND();
    //HANDLE pHandle = memory::getpHandle();

    
    bool running = true;

    //CreateExternalWindow(memory::getHWND());

    window::create(memory::getHWND());

    

    

    while (true) 
    {



        cheat::present();

        window::draw_rectangle(vec2i(20, 20), vec2i(50, 50), window::BRUSH_RED);

    }

    std::cout << std::endl << "Closing Window!" << std::endl;
    return 0;
}


void init() {
    std::cout << "========================================================================="                                                           << "\n";
    std::cout << "========================= " << ANSI_COLOR_MAGENTA << "ASSSAULT CUBE EXTERNAL "    << ANSI_COLOR_RESET << "======================== " << "\n";
    std::cout << "========================================================================="                                                           << "\n\n";
}