#include "math.h"
#include "utils.h"
#include <iostream>


// [x_s, y_s] = ProjectionMatrix * ViewMatrix * ModelMatrix * [x_w, y_w, z_w, 1]
v2i math::WorldToScreen(v3 pos, float matrix[16])
{
	// convert world space into clip space
	v4 clip_space = {
		pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12],
		pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13],
		pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14],
		pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15]
	};

	if (clip_space.w < 0.1f)
		return v2i{ -1, -1 };


	// convert clip space to normalized device coordinates
	v3 NDC = {
		clip_space.x / clip_space.w,
		clip_space.y / clip_space.w,
		clip_space.z / clip_space.w
	};

	// conver ndc to screen coordinates
	v2 screen_coords = {
		((screen.width   / 2) * NDC.x) + (NDC.x + screen.width/2),
		((-screen.height / 2) * NDC.y) + (NDC.y + screen.height/2),
	};

	return (v2i)screen_coords;
}

f32 math::distance(v2 a, v2 b) 
{
	return (f32)sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
}

f32 math::distance(v3 a, v3 b) 
{
	return (f32)sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y) + (b.z-a.z)*(b.z-a.z));
}

v3 math::CalculateAngles(v3 pPos, v3 ePos) 
{
	return v3{ 0, 0, 0 };
}