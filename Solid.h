#include <iostream>
#include <vector>
#include "Face.h"
#include "Globals.h"

using namespace std;

class Solid {
public:
    vector<coord> vertex;
    vector<vector<int>> face;

    void addVertex(double x, double y, double z) {
        coord temp = {x, y, z};
        vertex.push_back(temp);
    }

    void addFace(vector<int> points) {
        face.push_back(points);
    }

    Face getFace(int faceN) {
        Face curFace = Face(face[faceN].size());
        for (int a = 0; a < face[faceN].size(); a++) {
            curFace.setCorner(vertex[face[faceN][a]].x, vertex[face[faceN][a]].y, vertex[face[faceN][a]].z, a);
        }
        curFace.updateCoords();
        curFace.calcNormal();
        return curFace;
    }

    void rotateX(double angle) {
        double tempz, tempy;
        for (int a = 0; a < vertex.size(); a++) {
            tempy = vertex[a].y;
            tempz = vertex[a].z;
            vertex[a].y = tempy * cos(angle) - tempz * sin(angle);
            vertex[a].z = tempy * sin(angle) + tempz * cos(angle);
        }
    }

    void rotateY(double angle) {
        double tempx, tempz;
        for (int a = 0; a < vertex.size(); a++) {
            tempx = vertex[a].x;
            tempz = vertex[a].z;
            vertex[a].x = tempx * cos(angle) + tempz * sin(angle);
            vertex[a].z = -tempx * sin(angle) + tempz * cos(angle);
        }
    }

    void rotateZ(double angle) {
        double tempx, tempy;
        for (int a = 0; a < vertex.size(); a++) {
            tempx = vertex[a].x;
            tempy = vertex[a].y;
            vertex[a].x = tempx * cos(angle) - tempy * sin(angle);
            vertex[a].y = tempx * sin(angle) + tempy * cos(angle);
        }
    }

    void transform(double dx, double dy, double dz) {
        for (int a = 0; a < vertex.size(); a++) {
            vertex[a].x += dx;
            vertex[a].y += dy;
            vertex[a].z += dz;
        }
    }


    void sortFaces(int low, int high) {
        int i = low;
        int j = high;
        double pivot = vertex[face[(i + j) / 2][0]].z;
        double temp;

        while (i <= j) {
            while (vertex[face[i][0]].z < pivot) {
                i++;
            }

            while (vertex[face[j][0]].z > pivot) {
                j--;
            }

            if (i <= j) {
                for (int a = 0; a < 4; a++) {
                    temp = face[i][a];
                    face[i][a] = face[j][a];
                    face[j][a] = temp;
                }
                i++;
                j--;
            }
        }
        if (j > low) {
            sortFaces(low, j);
        }

        if (i < high) {
            sortFaces(i, high);
        }
    }

    void draw(SDL_Renderer *renderer) {
        sortFaces(0, face.size() - 1);
        //printf("%d, %d, %d. %d \n", ex.xVec[0], ex.xVec[1], ex.xVec[2], ex.xVec[3]);
        for (int faceN = face.size() - 1; faceN > -1; faceN--) {
            Face curFace = getFace(faceN);
            curFace.calcShade();
            if (curFace.visible) {
                curFace.draw(renderer);
            }
        }
    }

    void clear() {
        face.clear();
        vertex.clear();
    }
};
