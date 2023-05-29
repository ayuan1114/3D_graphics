#include <iostream>
#include <SDL.h>
#include <cmath>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include "Solid.h"
#include "Globals.h"

using namespace std;

class Framework {
public:
    // Constructor which initialize the parameters.
    Framework() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);      // setting draw color
        SDL_RenderClear(renderer);      // Clear the newly created window
        SDL_RenderPresent(renderer);    // Reflects the changes done in the
        //  window.
    }

    // Destructor
    ~Framework() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void shapeSetUp(int shape) {
        ex.clear();

        if (shape == 1) {
            int ptsSpin = 50, ptsRing = 50;
            double x, y, r = 150, R = 200; // the R is the radius of the whole donut, r is thickness of the donut
            for (int spin = 0; spin < ptsSpin; spin++) {
                for (int ring = 0; ring < ptsRing; ring++) {
                    x = R + r * cos(((2 * M_PI) / ptsRing) * ring);
                    y = r * sin(((2 * M_PI) / ptsRing) * ring);
                    ex.addVertex(x * cos(((2 * M_PI) / ptsSpin) * spin), y, -x * sin(((2 * M_PI) / ptsSpin) * spin));
                }
            }

            for (int spin = 0; spin < ptsSpin; spin++) {
                for (int ring = 0; ring < ptsRing; ring++) {
                    ex.addFace({spin * ptsRing + ring, ((spin + 1) % ptsSpin) * ptsRing + ring,
                                ((spin + 1) % ptsSpin) * ptsRing + ((1 + ring) % ptsRing), spin * ptsRing + ((1 + ring) % ptsRing)});
                }
            }
        }

        else if (shape == 2) {
            ex.addVertex(0, 250, 0);
            ex.addVertex(0, -250 * (1 / 3), 250 * (2 * sqrt(2) / 3));
            ex.addVertex(250 * ((2 * sqrt(2) / 3)) * cos(M_PI / 6), -250 * (1 / 3), -250 * ((2 * sqrt(2)) / 3) * sin(M_PI / 6));
            ex.addVertex(-250 * ((2 * sqrt(2)) / 3) * cos(M_PI / 6), -250 * (1 / 3), -250 * ((2 * sqrt(2)) / 3) * sin(M_PI / 6));

            ex.addFace({0, 2, 1});
            ex.addFace({0, 3, 2});
            ex.addFace({0, 1, 3});
            ex.addFace({1, 2, 3});
        }

        else if (shape == 3) {
            printf("123123");
            ex.addVertex(-250, 250, 250);
            ex.addVertex(250, 250, 250);
            ex.addVertex(250, -250, 250);
            ex.addVertex(-250, -250, 250);
            ex.addVertex(-250, 250, -250);
            ex.addVertex(250, 250, -250);
            ex.addVertex(250, -250, -250);
            ex.addVertex(-250, -250, -250);

            ex.addFace({0, 1, 2, 3});
            ex.addFace({0, 4, 5, 1});
            ex.addFace({1, 5, 6, 2});
            ex.addFace({2, 6, 7, 3});
            ex.addFace({3, 7, 4, 0});
            ex.addFace({7, 6, 5, 4});
        }
    }

    void gameLoop(int shape) {
        int close = 0;
        SDL_Event event;

        double rotX = 0;
        double rotY = 0;
        double rotZ = 0;

        int prevX, prevY;
        int curX, curY;
        bool Rdown = false;
        bool mouseMove, mouseDown;

        shapeSetUp(shape);

        while (close != 1) {
            SDL_RenderClear(renderer);
            if (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_QUIT:
                        close = 1;
                        break;
                    /*
                    case SDL_KEYDOWN:
                        printf("\n");
                        switch(event.key.keysym.scancode) {
                            case SDL_SCANCODE_W:
                                ex.rotateX(M_PI / 6);
                                break;
                            case SDL_SCANCODE_S:
                                ex.rotateX(-M_PI / 6);
                                break;
                            case SDL_SCANCODE_A:
                                ex.rotateY(M_PI / 6);
                                break;
                            case SDL_SCANCODE_D:
                                ex.rotateY(-M_PI / 6);
                                break;
                            case SDL_SCANCODE_Q:
                                ex.rotateZ(M_PI / 6);
                                break;
                            case SDL_SCANCODE_E:
                                ex.rotateZ(-M_PI / 6);
                                break;
                        }
                        for (int a = 0; a < ex.vertex.size(); a++) {
                            printf("(%f, %f, %f) ", ex.vertex[a].x, ex.vertex[a].y, ex.vertex[a].z);
                        }
                        */
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.scancode) {
                            case SDL_SCANCODE_W:
                                if (rotX < 1) {
                                    rotX++;
                                }
                                break;
                            case SDL_SCANCODE_S:
                                if (rotX > -1) {
                                    rotX--;
                                }
                                break;
                            case SDL_SCANCODE_A:
                                if (rotY < 1) {
                                    rotY++;
                                }
                                break;
                            case SDL_SCANCODE_D:
                                if (rotY > -1) {
                                    rotY--;
                                }

                                break;
                            case SDL_SCANCODE_Q:
                                if (rotZ < 1) {
                                    rotZ++;
                                }
                                break;
                            case SDL_SCANCODE_E:
                                if (rotZ > -1) {
                                    rotZ--;
                                }
                                break;
                            case SDL_SCANCODE_BACKSPACE:
                                shapeSetUp(shape);
                            case SDL_SCANCODE_SPACE:
                                rotX = 0;
                                rotY = 0;
                                rotZ = 0;
                                break;
                            case SDL_SCANCODE_R:
                                Rdown = !Rdown;
                                break;
                            case SDL_SCANCODE_T:
                                ex.transform(5, 0, 0);
                                break;
                            case SDL_SCANCODE_G:
                                ex.transform(-5, 0, 0);
                                break;
                            case SDL_SCANCODE_Y:
                                ex.transform(0, 5, 0);
                                break;
                            case SDL_SCANCODE_H:
                                ex.transform(0, -5, 0);
                                break;
                            case SDL_SCANCODE_U:
                                ex.transform(0, 0, 5);
                                break;
                            case SDL_SCANCODE_J:
                                ex.transform(0, 0, -5);
                                break;
                        }
                        break;

                    case SDL_MOUSEMOTION:
                        if (abs(event.motion.x - prevX) >= 5) {
                            prevX = curX;
                            curX = event.motion.x;
                        }
                        if (abs(event.motion.y - prevY) >= 5) {
                            prevY = curY;
                            curY = event.motion.y;
                        }
                        mouseMove = true;
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        mouseDown = true;
                        break;
                    case SDL_MOUSEBUTTONUP:
                        mouseDown = false;
                        break;
                }

            }

            if (mouseDown) {
                if (mouseMove) {
                    if (Rdown) {
                        if (abs(curX - prevX) >= 5) {
                            ex.rotateZ((M_PI / 180) * ((prevX - curX) / 5));
                        }
                    }
                    else {
                        if (abs(curX - prevX) >= 5) {
                            ex.rotateY((M_PI / 180) * ((prevX - curX) / 5));
                        }
                        if (abs(curY - prevY) >= 5) {
                            ex.rotateX((M_PI / 180) * ((prevY - curY) / 5));
                        }
                    }
                    mouseMove = false;
                }
            }

            ex.rotateX((M_PI / 180) * rotX);
            ex.rotateY((M_PI / 180) * rotY);
            ex.rotateZ((M_PI / 180) * rotZ);

            ex.draw(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000 / fps);

        }
    }

private:
    SDL_Window *window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Solid ex = Solid();
};



int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING); // Initializing SDL as Video
    Framework fw;
    fw.gameLoop(1);
    return 0;
}
