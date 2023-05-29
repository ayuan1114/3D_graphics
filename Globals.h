//
// Created by Aaron on 5/23/2023.
//
#include <SDL.h>
#include <cmath>

#ifndef INC_3D_GRAPHICS_GLOBALS_H
#define INC_3D_GRAPHICS_GLOBALS_H

// +x right
// -x left
// +y up
// -y down
// +z out of page
// -z into page
struct coord {
    double x, y, z;
};

double magnitude (double x, double y, double z) {
    return sqrt(x * x + y * y + z * z);
}
const double light[3] = {0, 0, -1};
const double lightMag = 1;
const int fps = 120;
const int screenW = 1000, screenH = 1000;

#endif //INC_3D_GRAPHICS_GLOBALS_H
