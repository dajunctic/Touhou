#ifndef TOUHOU_H_
#define TOUHOU_H_

#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <set>

#include <SDL.h>
#include <SDL_image.h>

static SDL_Window* window = NULL;
static SDL_Renderer* screen = NULL;
static SDL_Event* event = NULL;

const int FPS = 60; /* Frame per second*/

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 0;


const int RENDER_DRAW_COLOR = 0xFF;

enum KEY{
    K_RIGHT,
    K_LEFT,
    K_DOWN,
    K_UP
};

using namespace std;

#endif // !TOUHOU_H_