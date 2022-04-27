#ifndef TOUHOU_H_
#define TOUHOU_H_

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <utility>
#include <fstream>
#include <numeric>
#include <vector>
#include <string>
#include <math.h>
#include <queue>
#include <stack>
#include <map>
#include <set>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

#define fi first
#define se second

const double PI = 3.1415926;

const int FPS = 60; /* Frame per second*/

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 0;


const int RENDER_DRAW_COLOR = 0xFF;

const int BOARD_X = 340;
const int BOARD_Y = 0;
const int BOARD_LIMITED_X = 1280;
const int BOARD_LIMITED_Y = 720;

enum KEYBOARD_INPUT{
    K_LEFT,
    K_RIGHT,
    K_UP,
    K_DOWN
};

#endif // !TOUHOU_H_