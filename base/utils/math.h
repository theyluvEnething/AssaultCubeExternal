#pragma once

#include "../utils/utils.h"

class math
{
public:
	static v2i WorldToScreen(v3 pos, float matrix[16]);
	static f32 distance(v2 a, v2 b);
	static f32 distance(v3 a, v3 b);

	static v3 CalculateAngles(v3 pPos, v3 ePos);
};

