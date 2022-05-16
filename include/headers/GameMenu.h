#if !defined(GAME_MENU_H_)
#define GAME_MENU_H_

#include "Touhou.h"
#include "GameImage.h"
#include "GameText.h"
#include "MusicList.h"



class Menu{

public:
    enum MENU{
        MAIN, 
        EPISODES,
        OPTIONS,
        MUSIC,
        QUIT
    };
    enum OPTIONS{
        SETTING,
        HOW_TO_PLAY,
        ABOUT,
        BACK
    };

    enum SETTING{
        MUSIC_VOLUME,
        SOUND_VOLUME,
        DISPLAY,
        LANGUAGE
    };

    Menu();
    ~Menu();

    void load(SDL_Renderer * renderer);
    void show(SDL_Renderer * renderer);
    void updateInfo();
    bool isLocked();
    void HandleInput(SDL_Event e, bool * quit, SDL_Window * window, int * SCENE);
    bool isFullScreen = true;

    void ToggleFullScreen(SDL_Window* window, bool currentState);

private:

    Image choice;
    Image hover;

    int current_choice = 0; /* display choice in menu */
    int total_choice = 5; /* Total dishes in menu */
    int current_page = 0; /* display chosen page in menu */

    /*################# Options ################ */
    Image options;
    int option_pages = 4; 
    int current_option_page = SETTING;

    Image setting;
    Image level;
    Image select;
    Image tick;
    Image esc;
    int current_setting = -1;
    double sound_volume = 50; // %
    double music_volume = 50; // %
    bool current_display = true;


    Image how_to_play;
    Image about;
    Image back;

    /*################# Music ################ */
    Image theme;
    int current_song = 0;
    SongList music;
    Text music_text;
    Text music_gui;
    Animation dance[2];

    /*################# EPISODES ################ */

    Image eps_lock;
    Image eps_unlock;
    Image eps_select;
    Image eps_tail;
    Image wallpaper;
    int current_eps = 0;
    int total_eps = 2;
    bool is_lock = true;
    bool is_wallpaper = false;

};

#endif // GAME_MENU_H_
