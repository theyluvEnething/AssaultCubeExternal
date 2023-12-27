#pragma once

#include "../utils/utils.h"

typedef struct entity {
	f32 view_matrix[16];
	vector3 pos;

	int ammo;
	int health;
	char name[64];

	void print();
	void print_angles();
};
