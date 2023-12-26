#pragma once
#include <Windows.h>
#include "../utils/utils.h"

class window {

private:
	static HWND hwnd;
	static HDC hdc;

public:
	static const HBRUSH BRUSH_RED;
	static const HBRUSH BRUSH_GREEN;
	static const HBRUSH BRUSH_BLUE;


	static void create(HWND game_hwnd);
	static void draw_rectangle(v2i pos, v2i size, HBRUSH brushColor);
};