#include "window.h"
#include <sstream>
#include <iostream>

#pragma warning(disable : 4996) // disable strcopy (overflow)
#pragma warning(disable : 4244) // disable loss of data conversion

HWND window::hwnd;
HDC window::hdc;

const HBRUSH window::BRUSH_RED = CreateSolidBrush(RGB(255, 0, 0));
const HBRUSH window::BRUSH_GREEN = CreateSolidBrush(RGB(0, 255, 0));
const HBRUSH window::BRUSH_BLUE = CreateSolidBrush(RGB(0, 0, 255));

void window::create(HWND game_hwnd) 
{
	window::hwnd = game_hwnd;
	window::hdc = GetDC(game_hwnd);
}

void window::draw_rectangle(v2i pos, v2i size, HBRUSH brushColor) 
{
	RECT rect = { pos.x, pos.y, pos.x+size.x, pos.y+size.y};
	FillRect(window::hdc, &rect, brushColor);
}