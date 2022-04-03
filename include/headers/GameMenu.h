#if !defined(GAME_MENU_H_)
#define GAME_MENU_H_

#include "Touhou.h"
#include "GameImage.h"

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

    void Load(SDL_Renderer * screen){
        choice.Load(screen, "res/gui/menu.png");
        hover.Load(screen, "res/gui/hover.png");
        options.Load(screen, "res/gui/option.png");
        setting.Load(screen, "res/gui/setting.png");
        how_to_play.Load(screen, "res/gui/how_to_play.png");
        about.Load(screen, "res/gui/about.png");
        back.Load(screen, "res/gui/back.png");

        level.Load(screen, "res/gui/level.png");
        select.Load(screen, "res/gui/select.png");
        tick.Load(screen, "res/gui/tick.png");
        esc.Load(screen, "res/gui/esc.png");

    }
    void show(SDL_Renderer * screen){
        if(current_page == MAIN){
            int y = current_choice * 66 + 343;
            int x = (336  - hover.GetRect().w) / 2;
            hover.SetRect(x, y);
            hover.Render(screen);

            choice.Render(screen);
        }

        if(current_page == OPTIONS){
            options.Render(screen);

            if(current_option_page == SETTING){
                if(current_setting != -1){
                    if(current_setting < 2)
                        select.SetRect(170 , 200  + 40 * current_setting);
                    else
                        select.SetRect(170 , 246  + 42 * current_setting);
                    select.Render(screen);


                    esc.SetRect((SCREEN_WIDTH - esc.GetRect().w)/2, SCREEN_HEIGHT - esc.GetRect().h);
                    esc.Render(screen);
                }

                setting.Render(screen);

                level.SetRect(605.0 + 4.66 * music_volume , 200);
                level.Render(screen);

                level.SetRect(605.0 + 4.66 * sound_volume , 242);
                level.Render(screen);

                if(current_display)
                    tick.SetRect(590, 334);
                else
                    tick.SetRect(811, 334);
                
                tick.Render(screen);
                tick.SetRect(590, 374);
                tick.Render(screen);
            }

            if(current_option_page == HOW_TO_PLAY){
                how_to_play.Render(screen);
            }

            if(current_option_page == ABOUT){
                about.Render(screen);
            }

            if(current_option_page == BACK){
                back.Render(screen);
            }
        }
        
    }
    void HandleInput(SDL_Event e, bool * quit, SDL_Window * window);
    bool isFullScreen = true;

    void ToggleFullScreen(SDL_Window* window, bool currentState){
        isFullScreen = !currentState;

        SDL_SetWindowFullscreen(window, !currentState);
        SDL_ShowCursor(currentState);
    }

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

};

#endif // GAME_MENU_H_
