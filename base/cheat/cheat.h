#pragma once
#include "../data/entity.h"


class cheat
{
private:
	static entity player;
public:
	static int hook();
	static int setup();
	static int present();
	static void esp();
};

