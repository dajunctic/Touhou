#include "Game.h"


void Game::load(){
    /* Load Title Introduction */{
        dazu.Load(screen, "res/img/Dazu.png");
        dazu_warning.Load(screen, "res/img/warning.png");
        dazu.SetAlpha(dazu_alpha);
        dazu_sound = Mix_LoadWAV("res/sfx/DazuDazuGamer.wav");
        dazu_bg = Mix_LoadWAV("res/sfx/horror.wav");
    }
    /* Load Menu */{
        for(int i = 0 ; i < 4 ; i++)
        {
            string path = "res/img/bg/menu_bg_0" + to_string(i) + ".jpg";
            menu_bg[i].Load(screen, path);
        }
        menu_bgm = Mix_LoadMUS("res/bgm/YourReality.mp3");
        tv = Mix_LoadWAV("res/sfx/tv.wav");
        menu.load(screen);
    }
    stage.Load(screen);
}

void Game::display()
{
    if(SCENE == TITLE)
    {
        if(time.CheckTime(2 , 0))
            Mix_PlayChannel(-1, dazu_sound , 0); 

        if(time.CheckTime(0 , 1))
            Mix_PlayChannel(-1, dazu_bg , 0); 
        
        if(time.CheckPeriod(0, 4)){
            if(dazu_alpha + 1 > 255) dazu_alpha = 255;
            else dazu_alpha += 1;
        }
        else{
            if(dazu_alpha - 1 < 0) dazu_alpha = 0;
            else dazu_alpha -= 1;
        }
        
        if(time.CheckPeriod(0, 10)){
            dazu.SetAlpha(dazu_alpha);
            dazu.Render(screen);
        }

        if(time.CheckTime(8))
            Mix_PlayChannel(-1, tv, 0);
        if(time.CheckTime(11)){
            Mix_HaltChannel(-1);
            time.Reset();
            SCENE = MENU;
        }
    }
    if(SCENE == MENU)
    {
        if(time.CheckTime(0 , 1)){
            Mix_PlayMusic(menu_bgm, -1);
            menu.updateInfo();
        }

        if(time.GetSeconds() % 4 == 0 and time.GetFrameTime() == 0){
            current_menu_bg ++;
            current_menu_bg %= 4;
        }
        menu_bg[current_menu_bg].Render(screen);
        menu.show(screen);
    }
    if(SCENE == PLAY)
    {
        stage.Show(screen);
    }

}

void Game::HandleInput(SDL_Event e)
{
    if(SCENE == PLAY)
    {
        stage.HandleInput(e, &SCENE);
        if(SCENE == MENU)
        {
            menu.setReturn(true);
            stage.setScene(0);
            stage.reset();
            return;
        }
    }
    if(SCENE == MENU){
        menu.HandleInput(e, &quit, window, &SCENE);
        if(SCENE == PLAY) stage.setNotification(menu.isLocked());
        return;
    }
}