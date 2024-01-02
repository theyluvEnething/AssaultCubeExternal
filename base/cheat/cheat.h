#pragma once
#include "../data/entity.h"
#include <stdint.h>
#include <vector>
#include <stdbool.h>

class cheat
{
private:
	static entity player;
	static uint32_t box_size;
	static std::vector<entity> entityArr;
	
	static std::vector<entity> getEntityArr();
	static void updateLocalPlayer();
	static bool inFOV(v3 pos);
public:
	static int hook();
	static int setup();
	static int present();
	static void esp();
	static void aimbot();

	static f32 FOV;
};

