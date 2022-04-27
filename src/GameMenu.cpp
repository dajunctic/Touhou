#include "GameMenu.h"

Menu::Menu(){
    
}

Menu::~Menu(){

}

void Menu::HandleInput(SDL_Event e, bool * quit, SDL_Window * window, int * SCENE){
    if(e.type == SDL_KEYDOWN){
        if(current_page == MAIN){
            switch (e.key.keysym.sym){
            case SDLK_DOWN:
                current_choice ++;
                current_choice %= total_choice;
                break;
            
            case SDLK_UP:
                current_choice += (total_choice - 1);
                current_choice %= total_choice;
                break;
            
            case SDLK_RETURN:
                /* Options */
                if(current_choice == OPTIONS){
                    current_page = OPTIONS;
                }
                if(current_choice == MAIN){
                    *SCENE = 2;
                }
                /* Quit */
                if(current_choice == QUIT) 
                    *quit = true;
                break;
            
            default:
                break;
            }
        }
        if(current_page == OPTIONS){
            switch (e.key.keysym.sym){
            case SDLK_DOWN:
                if(current_setting == -1){
                    current_option_page ++;
                    current_option_page %= option_pages;
                    break;
                }

                if(current_option_page == SETTING){
                    current_setting ++;
                    current_setting %= 4;
                }
                break;
            
            case SDLK_UP:
                if(current_setting == -1){
                    current_option_page += (option_pages - 1);
                    current_option_page %= option_pages;
                    break;
                }

                if(current_option_page == SETTING){
                    current_setting += 3;
                    current_setting %= 4;
                }
                break;

            case SDLK_RETURN:

                if(current_option_page == BACK){
                    current_option_page = SETTING;
                    current_page = MAIN;
                }
                break;

            case SDLK_LEFT:
                if(current_option_page == SETTING){
                    if(current_setting == MUSIC_VOLUME){
                        music_volume --;
                        if(music_volume < 0) music_volume = 0;
                        Mix_VolumeMusic(music_volume * 128 / 100);
                    }
                    if(current_setting == SOUND_VOLUME){
                        sound_volume --;
                        if(sound_volume < 0) sound_volume = 0;
                        Mix_Volume(-1, sound_volume * 128 / 100);
                    }
                    if(current_setting == DISPLAY){
                        current_display = !current_display;
                        ToggleFullScreen(window, current_display);
                    }
                }
                break;
            case SDLK_RIGHT:
                if(current_option_page == SETTING){
                    if(current_setting == -1){
                        current_setting = MUSIC_VOLUME;
                        break;
                    }
                    if(current_setting == MUSIC_VOLUME){
                        music_volume ++;
                        if(music_volume > 100) music_volume = 100;
                        Mix_VolumeMusic(music_volume * 128 / 100);
                    }
                    if(current_setting == SOUND_VOLUME){
                        sound_volume ++;
                        if(sound_volume > 100) sound_volume = 100;
                        Mix_Volume(-1, sound_volume * 128 / 100);
                    }
                    if(current_setting == DISPLAY){
                        current_display = !current_display;
                        ToggleFullScreen(window, current_display);
                    }
                }
                break;
            case SDLK_ESCAPE:
                if(current_option_page == SETTING){
                    current_setting = -1;
                }
            
            default:
                break;
            }
        }
    }
}