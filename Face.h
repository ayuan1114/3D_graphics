#include <iostream>
#include <cmath>
#include "Globals.h"

using namespace std;

class Face {
public:
    int vertices;
    coord corner[4];
    double normal[3];
    double normalMag;
    Sint16 xVec[100000];
    Sint16 yVec[100000];
    double shade;
    int visible = 1;
    double visionVec[3] = {0, 0, -1};
    Face (int vertices) {
        for (int a = 0; a < vertices; a++) {
            corner[a] = {0, 0, 0};
        }
        this->vertices = vertices;
    }

    void setCorner (double x, double y, double z, int num) {
        corner[num] = {x, y, z};
    }

    void calcShade() {
        shade = (light[0] * normal[0] + light[1] * normal[1] + light[2] * normal[2]) / (normalMag * lightMag);
        if (shade > 0) {
            shade = 0;
        }
        if (visionVec[0] * normal[0] + visionVec[1] * normal[1] + visionVec[2] * normal[2] >= 0) {
            visible = 0;
        }
        else {
            visible = 1;
        }
    }

    void calcNormal() {
        normal[0] = (corner[vertices - 1].y - corner[0].y) * (corner[1].z - corner[0].z) - (corner[vertices - 1].z - corner[0].z) * (corner[1].y - corner[0].y);
        normal[1] = (corner[vertices - 1].z - corner[0].z) * (corner[1].x - corner[0].x) - (corner[vertices - 1].x - corner[0].x) * (corner[1].z - corner[0].z);
        normal[2] = (corner[vertices - 1].x - corner[0].x) * (corner[1].y - corner[0].y) - (corner[vertices - 1].y - corner[0].y) * (corner[1].x - corner[0].x);
        normalMag = magnitude(normal[0], normal[1], normal[2]);
    }

    void updateCoords() {
        for (int a = 0; a < 4; a++) {
            xVec[a] = (int) (corner[a].x + (screenW / 2));
            yVec[a] = (int) ((screenH / 2) - corner[a].y);
        }
    }

    void draw(SDL_Renderer *renderer) {
        filledPolygonRGBA(renderer, xVec, yVec, vertices, 0, 255 * abs(shade), 0, 255 * visible);
    }
};
