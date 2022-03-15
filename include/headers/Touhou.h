#ifndef TOUHOU_H_
#define TOUHOU_H_

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <utility>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <queue>
#include <stack>
#include <set>

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

#define fi first
#define se second

const double PI = 3.1415926;

const int FPS = 60; /* Frame per second*/

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 0;


const int RENDER_DRAW_COLOR = 0xFF;


struct TimeData{
    int sec; // second
    int min; // minute
    int hour; // hour
    TimeData(int h = 0, int m = 0, int s = 0){
        this->hour = h;
        this->min = m;
        this-> sec = s;
    }
};

enum KEYBOARD_INPUT{
    K_LEFT,
    K_RIGHT,
    K_UP,
    K_DOWN
};

#endif // !TOUHOU_H_