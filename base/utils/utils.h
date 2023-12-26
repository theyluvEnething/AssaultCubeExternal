#pragma once

#include <stdio.h>
#include <stdarg.h>

typedef float f32;
typedef double f64;


typedef struct vector2 { f32 x; f32 y; } v2;
typedef struct vector2i { int x; int y; } v2i;
#define vec2(x, y) v2{(f32)x, (f32)y}
#define vec2i(x, y) v2i{(int)x, (int)y}

typedef struct vector3 { f32 x; f32 y; f32 z; } v3;
typedef struct vector3i { int x; int y; int z; } v3i;
#define vec3(x, y, z) v3{(f32)x, (f32)y, (f32)z}
#define vec3i(x, y, z) v3i{(int)x, (int)y, (int)z}

typedef struct entity {
    vector3 pos;
    int health;
    char name[64];
};

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

static void print(const char* message, ...) {
    va_list args;
    va_start(args, message);
    printf(ANSI_COLOR_MAGENTA "[INFO] " ANSI_COLOR_RESET);
    vprintf(message, args);
    va_end(args);
}


