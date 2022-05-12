#if !defined(GAME_H_)
#define GAME_H_

#include "Touhou.h"
#include "GameImage.h"
#include "GameTime.h"
#include "GameMenu.h"
#include "GameStage.h"
#include "Character.h"
#include "Bullet.h"
#include "Enemy.h"

enum SCENENAME
{
    TITLE,
    MENU,
    PLAY
};

class Game{
private:
    SDL_Window* window = NULL;
    SDL_Renderer* screen = NULL;
    SDL_Event* event = NULL;

    int SCENE = PLAY;

    /* Title introduction */
    Image dazu;
    Image dazu_warning;
    Uint8 dazu_alpha = 0;

    Mix_Chunk* dazu_sound = NULL;
    Mix_Chunk* dazu_bg = NULL;
    Mix_Chunk* tv = NULL;

    /* Menu scene */
    int current_menu_bg = -1;
    Image menu_bg[4];
    Mix_Music* menu_bgm = NULL;
    Menu menu;



    /* New Game Screen */
    Time time;
    Stage stage;
     
public:

    bool quit = false;


    Game(){ 
        init();
    };
    ~Game(){};
    void init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            cerr <<  "Can't Init SDL";
            exit(0);
        }
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            cerr << "Warning: Linear texture filtering not enabled!" ;

        window = SDL_CreateWindow("Touhou - The Horror Night", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL)
            cerr <<  "Can't create window!";
        else {
            screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (screen == NULL) {
                cerr << "Can't create Screen by creating render!";
                exit(0);
            }
            else {
                SDL_SetRenderDrawColor(screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

                int pngImgFlags = IMG_INIT_PNG;
                int jpgImgFlags = IMG_INIT_JPG;

                if (!(IMG_Init(pngImgFlags) & pngImgFlags) or !(IMG_Init(jpgImgFlags) & jpgImgFlags)){
                    cerr << "SDL_Image Setting Failed";
                    exit(0);
                }
                SDL_Surface* icon = IMG_Load("res/img/icon.png");
                SDL_SetWindowIcon(window, icon);
            }
        }

        /* Init Sound and Music */
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
            printf("%s", Mix_GetError());
        }

        if (TTF_Init() < 0){
            SDL_Log("%s", TTF_GetError());
        }

        Mix_Volume(-1, 64);
        Mix_VolumeMusic(64);
    }
    void close() {
        /* Destroy window */
        SDL_DestroyRenderer(screen);
        SDL_DestroyWindow(window);
        screen = NULL;
        window = NULL;

        /*  Quit  SDL subsystems  */
        IMG_Quit();
        Mix_Quit();
        TTF_Quit();
        SDL_Quit();
    }
    void load();
    void run() {
        int DELAY_TIME = 1000 / FPS;
        Uint32 frameStart;
	    Uint32 frameTime;


        SDL_Event e;

        time.Start();

        while (!quit) 
        {
            frameStart = SDL_GetTicks();
            while (SDL_PollEvent(&e) != 0) 
            {
                if (e.type == SDL_QUIT)
                    quit = true;

                HandleInput(e);
            }
            SDL_SetRenderDrawColor(screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(screen);

            /*#########################################################*/
                            /* Sovle Display Problem */
            SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
            SDL_Rect r = {0, 0 , 1280 , 720};
            SDL_RenderFillRect( screen, &r );
            SDL_SetRenderDrawBlendMode(screen, SDL_BLENDMODE_BLEND);

            time.Update();

            display();
            /*#########################################################*/
            SDL_RenderPresent(screen);

            /*#########################################################*/
                    /* FPS Problem: Don't Edit or Fix */
            {
                frameTime = SDL_GetTicks() - frameStart;
                if (frameTime < DELAY_TIME){
                    SDL_Delay(DELAY_TIME - frameTime);
                }
            }
            /*#########################################################*/
        }
        close();
    }
    void display();

    void HandleInput(SDL_Event e);

};

#endif // GAME_H_
