#pragma once
#include <Windows.h>
#include <stdint.h>
#include "../utils/utils.h"

class window {

private:
	static HWND hwnd;
	static HDC hdc, hdc_buffer;
	static HBITMAP bitmap, bitmap_buffer;
	static HFONT font;

public:
	static const HBRUSH BRUSH_RED;
	static const HBRUSH BRUSH_GREEN;
	static const HBRUSH BRUSH_BLUE;
	static const HBRUSH BRUSH_PINK;
	static const HBRUSH BRUSH_MAGENTA;
	static const HBRUSH BRUSH_PURPLE;
	static const HBRUSH BRUSH_CYAN;
	static const HBRUSH BRUSH_LIGHT_GREEN;


	static void create(HWND game_hwnd);
	static void update();
	static void destroy();


	static void draw_rectangle(v2i pos, v2i size, HBRUSH brushColor);
	static void draw_rectangle(int left, int top, int right, int bottom, HBRUSH brushColor);
	static void draw_line(v2i start, v2i end, uint8_t thickness, HBRUSH brushColor);

	static void draw_corner_box(v2i pos, v2i size, uint8_t thickness, HBRUSH brushColor);
	static void draw_border_box(v2i left_top, v2i right_bottom, uint8_t thickness, HBRUSH brushColor);
	static void draw_circle(v2 pos, uint8_t rad, uint8_t thickness, HBRUSH brushColor);

};