#pragma once

#include <stdio.h>
#include <stdarg.h>


typedef float f32;
typedef double f64;


// struct { int xPos; int yPos; int height; int width; } extern screen;
typedef struct vector2
{
    f32 x; f32 y;

    vector2(int _x, int _y) : x((f32)_x), y((int)_y) {}
    vector2(f32 _x, f32 _y) : x(_x), y(_y) {}

    vector2() : x(0), y(0) {}


} v2;



struct Screen { int xPos; int yPos; int width; int height; v2 center; };
extern struct Screen screen;



typedef struct vector2i 
{ 
    int x; int y; 

    // vector2i(int _x, int _y) : x(_x), y(_y) {}

    explicit vector2i(vector2 vec) : x(vec.x), y(vec.y) {}
    explicit vector2i(int _x, int _y) : x(_x), y(_y) {}

} v2i;

#define vec2(x, y) v2{(f32)x, (f32)y}
#define vec2i(x, y) v2i{(int)x, (int)y}

typedef struct vector3 {
   f32 x; f32 y; f32 z; 

   vector3(float _x, float _y, float _z) {
       this->x = _x;
       this->y = _y;
       this->z = _z;
   }

   vector3() {
       this->x = 0.0f;
       this->y = 0.0f;
       this->z= 0.0f;
   }

   vector3 operator+ (vector3& a) {
       return vector3(x + a.x, y + a.y, z + a.z);
   }

   vector3 operator- (vector3& a) {
       return vector3(x - a.x, y - a.y, z - a.z);
   }

   vector3 operator/ (vector3& a) {
       return vector3(x / a.x, y / a.y, z / a.z);
   }

   vector3 operator* (vector3& a) {
       return vector3(x * a.x, y * a.y, z * a.z);
   }

} v3;

typedef struct vector3i { int x; int y; int z; } v3i;
#define vec3(x, y, z) v3{(f32)x, (f32)y, (f32)z}
#define vec3i(x, y, z) v3i{(int)x, (int)y, (int)z}

typedef struct vector4 { f32 x; f32 y; f32 z; f32 w; } v4;
typedef struct vector4i { int x; int y; int z; int w; } v4i;


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


