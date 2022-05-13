#ifndef GAME_STORY_H
#define GAME_STORY_H

#include "Touhou.h"
#include "GameImage.h"
#include "GameTime.h"
#include "GameText.h"

class Story{
private:
    Image textbox;
    Image message_line;
    
    Text name;

    Dialogue dialogue;

    Animation transition;
    double transition_x = 1200;
    double transition_y = 640;
    double transition_speed = 0.5;

    bool loadBg = true;
    Image bgImg;
    vector<string> bg;
    map<string, string> bgMap; 

    vector<pair<string,string> > scripts; // Đoạn hội thoại
    int current_script; // Lời thoại
    bool next_script;

    Image rh, rh_happy, rh_surprise, rh_blink, rh_shy; // Reimu Hakurei
    Image am, am_sad, am_blink; // Alice Margatroid


    Mix_Music * bgm = NULL;
    bool is_play_music;

public:
    Story();
    ~Story();
    void load(SDL_Renderer *);
    void show(SDL_Renderer *);
    void showBackground(SDL_Renderer *);
    void showCharacter(SDL_Renderer *);
    void handleInput(SDL_Event e, int * scene);

    /*left c-left center c-right right */
    int getPosX(string, SDL_Rect);
    int getPosY(SDL_Rect);
    
};

#endif // !GAME_STORY_H