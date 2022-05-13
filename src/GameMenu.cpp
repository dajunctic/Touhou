#include "GameMenu.h"

Menu::Menu()
{
    Mix_VolumeMusic(music_volume * 128 / 100);
    Mix_Volume(-1, sound_volume * 128 / 100);
}

Menu::~Menu()
{

}

void Menu::load(SDL_Renderer * renderer)
{
    choice.Load(renderer, "res/gui/menu.png");
    hover.Load(renderer, "res/gui/hover.png");
    options.Load(renderer, "res/gui/option.png");
    setting.Load(renderer, "res/gui/setting.png");
    how_to_play.Load(renderer, "res/gui/how_to_play.png");
    about.Load(renderer, "res/gui/about.png");
    back.Load(renderer, "res/gui/back.png");

    level.Load(renderer, "res/gui/level.png");
    select.Load(renderer, "res/gui/select.png");
    tick.Load(renderer, "res/gui/tick.png");
    esc.Load(renderer, "res/gui/esc.png");
    theme.Load(renderer, "res/gui/theme.png");

    music.readFile("res/dat/music_list.txt");
    music.loadMusic("res/dat/music_name_file.txt");
    music.print();
    music_text.setSize(25);
    dance[0].set(20, 10);
    dance[0].setPos(920 , 100);
    dance[0].load(renderer, "res/gui/animation/dance1.png");
    dance[1].set(18, 10);
    dance[1].setPos(920 , 420);
    dance[1].load(renderer, "res/gui/animation/dance2.png");
}

void Menu::show(SDL_Renderer * renderer)
{
    if(current_page == MAIN){
        int y = current_choice * 66 + 343;
        int x = (336  - hover.GetRect().w) / 2;
        hover.SetRect(x, y);
        hover.Render(renderer);

        choice.Render(renderer);
    }
    if(current_page == OPTIONS)
    {
        options.Render(renderer);

        if(current_option_page == SETTING)
        {
            if(current_setting != -1)
            {
                if(current_setting < 2)
                    select.SetRect(170 , 200  + 40 * current_setting);
                else
                    select.SetRect(170 , 246  + 42 * current_setting);
                select.Render(renderer);


                esc.SetRect((SCREEN_WIDTH - esc.GetRect().w)/2, SCREEN_HEIGHT - esc.GetRect().h);
                esc.Render(renderer);
            }

            setting.Render(renderer);

            level.SetRect(605.0 + 4.66 * music_volume , 200);
            level.Render(renderer);

            level.SetRect(605.0 + 4.66 * sound_volume , 242);
            level.Render(renderer);

            if(current_display)
                tick.SetRect(590, 334);
            else
                tick.SetRect(811, 334);
            
            tick.Render(renderer);
            tick.SetRect(590, 374);
            tick.Render(renderer);
        }

        if(current_option_page == HOW_TO_PLAY)
        {
            how_to_play.Render(renderer);
        }

        if(current_option_page == ABOUT)
        {
            about.Render(renderer);
        }

        if(current_option_page == BACK)
        {
            back.Render(renderer);
        }
    }
    if(current_page == MUSIC)
    {
        theme.Render(renderer);
        for(int i = 0 ; i < music.size() ; i++)
        {   
            if(current_song == i) 
                music_text.setColor(renderer, 0, 204, 255);
            else 
                music_text.setColor(renderer, 255 , 255, 255);

            music_text.setText(renderer, to_string(i+1) + ". " + music.at(i));
            music_text.setPos(100 , 80 + i * 50);
            
            music_text.show(renderer);
        }
        
        music_text.setColor(renderer, 255 , 255, 255);
        music_text.setText(renderer, "[ Esc to return Home ]");
        music_text.setPos(SCREEN_WIDTH / 2 - music_text.getRect().w / 2, 680);
        music_text.show(renderer);

        dance[0].show(renderer);
        dance[1].show(renderer);

    }
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
                if(current_choice == OPTIONS)
                {
                    current_page = OPTIONS;
                }
                if(current_choice == MAIN)
                {
                    *SCENE = 2;
                    Mix_HaltMusic();
                }
                if(current_choice == MUSIC)
                {
                    current_page = MUSIC;
                }
                /* Quit */
                if(current_choice == QUIT) 
                    *quit = true;
                break;
            
            default:
                break;
            }
        }
        if(current_page == OPTIONS)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_DOWN:
                if(current_setting == -1)
                {
                    current_option_page ++;
                    current_option_page %= option_pages;
                    break;
                }

                if(current_option_page == SETTING)
                {
                    current_setting ++;
                    current_setting %= 4;
                }
                break;
            
            case SDLK_UP:
                if(current_setting == -1)
                {
                    current_option_page += (option_pages - 1);
                    current_option_page %= option_pages;
                    break;
                }

                if(current_option_page == SETTING)
                {
                    current_setting += 3;
                    current_setting %= 4;
                }
                break;

            case SDLK_RETURN:

                if(current_option_page == BACK)
                {
                    current_option_page = SETTING;
                    current_page = MAIN;
                }
                break;

            case SDLK_LEFT:
                if(current_option_page == SETTING)
                {
                    if(current_setting == MUSIC_VOLUME)
                    {
                        music_volume --;
                        if(music_volume < 0) music_volume = 0;
                        Mix_VolumeMusic(music_volume * 128 / 100);
                    }
                    if(current_setting == SOUND_VOLUME)
                    {
                        sound_volume --;
                        if(sound_volume < 0) sound_volume = 0;
                        Mix_Volume(-1, sound_volume * 128 / 100);
                    }
                    if(current_setting == DISPLAY)
                    {
                        current_display = !current_display;
                        ToggleFullScreen(window, current_display);
                    }
                }
                break;
            case SDLK_RIGHT:
                if(current_option_page == SETTING)
                {
                    if(current_setting == -1)
                    {
                        current_setting = MUSIC_VOLUME;
                        break;
                    }
                    if(current_setting == MUSIC_VOLUME)
                    {
                        music_volume ++;
                        if(music_volume > 100) music_volume = 100;
                        Mix_VolumeMusic(music_volume * 128 / 100);
                    }
                    if(current_setting == SOUND_VOLUME)
                    {
                        sound_volume ++;
                        if(sound_volume > 100) sound_volume = 100;
                        Mix_Volume(-1, sound_volume * 128 / 100);
                    }
                    if(current_setting == DISPLAY)
                    {
                        current_display = !current_display;
                        ToggleFullScreen(window, current_display);
                    }
                }
                break;
            case SDLK_ESCAPE:
                if(current_option_page == SETTING)
                {
                    current_setting = -1;
                }
            
            default:
                break;
            }
        }
        if (current_page == MUSIC)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                
                current_page = MAIN;
                break;

            case SDLK_DOWN:
                current_song ++;
                current_song %= music.size();

                music.play(current_song);
                break;
            
            case SDLK_UP:
                current_song += music.size() - 1;
                current_song %= music.size();

                music.play(current_song);
                break;
                
            default:
                break;
            }
        }
    }
}

void Menu::ToggleFullScreen(SDL_Window* window, bool currentState){
    isFullScreen = !currentState;

    SDL_SetWindowFullscreen(window, !currentState);
    SDL_ShowCursor(currentState);
}