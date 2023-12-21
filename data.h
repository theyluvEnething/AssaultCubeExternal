#pragma once

typedef float f32;
typedef double f64;
typedef struct { f32 x; f32 y; f32 z; } vector3;

typedef struct entity {
    vector3 pos;
    int health;
    char name[64];
};