#include "window.h"
#include <sstream>
#include <iostream>
#include "../utils/utils.h"
#include "../memory/memory.h"
#include "../data/offsets.h"

#pragma warning(disable : 4996) // disable strcopy (overflow)
#pragma warning(disable : 4244) // disable loss of data conversion

HWND window::hwnd;
HDC window::hdc;
HDC window::hdc_buffer;
HBITMAP window::bitmap;
HBITMAP window::bitmap_buffer;
HFONT window::font;

const HBRUSH window::BRUSH_RED = CreateSolidBrush(RGB(255, 0, 0));
const HBRUSH window::BRUSH_GREEN = CreateSolidBrush(RGB(0, 255, 0));
const HBRUSH window::BRUSH_BLUE = CreateSolidBrush(RGB(0, 0, 255));
const HBRUSH window::BRUSH_PINK = CreateSolidBrush(RGB(255, 182, 193));
const HBRUSH window::BRUSH_MAGENTA = CreateSolidBrush(RGB(255, 0, 255));
const HBRUSH window::BRUSH_PURPLE = CreateSolidBrush(RGB(128, 0, 128));
const HBRUSH window::BRUSH_CYAN = CreateSolidBrush(RGB(0, 255, 255));
const HBRUSH window::BRUSH_LIGHT_GREEN = CreateSolidBrush(RGB(144, 238, 144));

void window::create(HWND game_hwnd) 
{
	window::hwnd = game_hwnd;
	window::hdc = GetDC(game_hwnd);
	window::hdc_buffer = CreateCompatibleDC(window::hdc);

}

void window::update() {
	
	memory::read(offset::iGameWidth, &screen.width, sizeof(screen.width));
	memory::read(offset::iGameHeight, &screen.height, sizeof(screen.height));
	screen.center = v2{ screen.width/2, screen.height/2 };
	
	//int x  = screen.xPos,
	//	y  = screen.xPos,
	//	cx = screen.width,
	//	cy = screen.height;
}

void window::draw_rectangle(v2i pos, v2i size, HBRUSH brushColor) 
{
	RECT rect = { pos.x-size.x/2, pos.y-size.y/2, pos.x+size.x/2, pos.y+size.y/2 };
	FillRect(window::hdc, &rect, brushColor);
}

void window::draw_rectangle(int left, int top, int right, int bottom, HBRUSH brushColor)
{
	RECT rect = { left, top, right, bottom };
	FillRect(window::hdc, &rect, brushColor);
}


void window::draw_line(v2i start, v2i end, uint8_t thickness, HBRUSH brushColor)
{
	
	HPEN Pen, bPen;		LOGBRUSH lbr;
	GetObject(brushColor, sizeof(lbr), &lbr) != sizeof(lbr);


	Pen = CreatePen(PS_SOLID, thickness, lbr.lbColor);
	bPen = (HPEN)SelectObject(hdc, Pen);

	MoveToEx(hdc, start.x, start.y, NULL);		// Move Pen to the starting point
	LineTo(hdc, end.x, end.y);					// Draw a line to the ending point	

	SelectObject(hdc, bPen);
	DeleteObject(Pen);
}

void window::draw_corner_box(v2i pos, v2i size, uint8_t thickness, HBRUSH brushColor) {
	RECT rect = { pos.x, pos.y, pos.x + size.x, pos.y + size.y};
}

void window::draw_border_box(v2i pos, v2i size, uint8_t thickness, HBRUSH brushColor) {
	draw_rectangle(pos.x-size.x/2, pos.y-size.y/2, pos.x+size.x/2, pos.y-size.y/2+thickness, brushColor);
	draw_rectangle(pos.x-size.x/2, pos.y+size.y/2, pos.x+size.x/2, pos.y+size.y/2-thickness, brushColor);
	draw_rectangle(pos.x-size.x/2, pos.y-size.y/2, pos.x-size.x/2+thickness, pos.y+size.y/2, brushColor);
	draw_rectangle(pos.x+size.x/2, pos.y-size.y/2, pos.x+size.x/2-thickness, pos.y+size.y/2, brushColor);


	//draw_rectangle(pos.x-size.x/2,	 pos.y+size.y/2,   pos.x+size.x/2,   thickness,			brushColor);
	//draw_rectangle(pos.x-size.x/2,	 pos.y-size.y/2,   thickness,		 pos.y+size.y/2,	brushColor);
	//draw_rectangle(pos.x+size.x/2,   pos.y-size.y/2,   thickness,		 pos.y+size.y/2,	brushColor);
}

void window::draw_circle(v2 pos, uint8_t rad, uint8_t thickness, HBRUSH brushColor) {
	//RECT aimbot_fov = { pos.x-rad, pos.y-rad, pos.x+rad, pos.y+rad };
	//Ellipse(window::hdc, aimbot_fov.left, aimbot_fov.top, aimbot_fov.right, aimbot_fov.bottom);

	for (int i = 0; i < 360; i++) {
		// x = a * cos(t) -> rad * cos(t)
	    // y = a * sin(t) -> rad * sin(t)
		int x = pos.x + rad*cos(i);
		int y = pos.y + rad * sin(i);

		RECT rect = { x, y, x+thickness, y+thickness };
		FillRect(window::hdc, &rect, brushColor);
	}
}

void window::destroy() {
	ReleaseDC(window::hwnd, window::hdc);
}