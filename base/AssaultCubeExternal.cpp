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
void out();

struct Screen screen;

int main(void*)
{
    init();
    cheat::hook();
    cheat::setup();

    window::create(memory::getHWND());


    for (;;) 
    {        
        cheat::present();

        cheat::esp();
        cheat::aimbot();

        window::draw_rectangle(vec2i(20, 20), vec2i(20, 20), window::BRUSH_RED);
        window::update();
    }


    out();
    return 0;
}


void init() {
    std::cout << "========================================================================="                                                        << "\n";
    std::cout << "========================= " << ANSI_COLOR_MAGENTA << "ASSSAULT CUBE EXTERNAL" << ANSI_COLOR_RESET << " ======================== " << "\n";
    std::cout << "========================================================================="                                                        << "\n" << std::endl;
}

void out() {
    std::cout << "=========================================================================" << "\n";
    std::cout << "========================= " << ANSI_COLOR_MAGENTA << "CLOSING WINDOW" << ANSI_COLOR_RESET << "======================== " << "\n";
    std::cout << "=========================================================================" << std::endl;
}