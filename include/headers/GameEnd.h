#ifndef GAME_END_H
#define GAME_END_H


#include "Touhou.h"
#include "GameImage.h"
#include "GameText.h"
#include "GameTime.h"

class End{
private:
    bool is_mystery = true;
    
    Image mystery_bg;
    Image Dajunctic;
    Image textbox;
    Dialogue mystery;

    Dialogue postscript1;
    Dialogue postscript2;
    string script1;
    string script2;

    Image thanks;

    Text back;
    bool isBack = false;
    
    
    Mix_Music* bg;
    bool isBgm = false;
    Mix_Chunk* thankyou;
    bool isThank = false;

public:
    End();
    ~End();

    void load(SDL_Renderer * renderer);
    void show(SDL_Renderer * renderer);
    void handleInput(SDL_Event, int *);
};


#endif // !GAME_END_H