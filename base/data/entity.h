#pragma once

#include "../utils/utils.h"

typedef struct entity {
	f32 view_matrix[16];
	v3 pos;
	v2 viewangle;

	int ammo;
	int health;
	char name[64];

	void print();
	void print_angles();
	void print_important();

	entity() : view_matrix{}, pos{0, 0, 0}, viewangle{0, 0}, ammo(0), health(0), name{""} {}
};
