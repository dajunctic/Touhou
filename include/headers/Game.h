#if !defined(GAME_H_)
#define GAME_H_

#include "Touhou.h"
#include "GameObject.h"
#include "Character.h"
#include "Bullet.h"
#include "ImpTimer.h"

class Game{

private:
    SDL_Window* window = NULL;
    SDL_Renderer* screen = NULL;
    SDL_Event* event = NULL;


    multiset<int> Key;

    GameTime MainTime;
    Character Hakurei;  
public:

    Game(){ 
        init();
        load();
    };
    ~Game(){};
    void init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            cerr <<  "Can't Init SDL";
            exit(0);
        }
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            cerr << "Warning: Linear texture filtering not enabled!" ;

        window = SDL_CreateWindow("Touhou", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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
    }
    void close() {
        /* Destroy window */
        SDL_DestroyRenderer(screen);
        SDL_DestroyWindow(window);
        screen = NULL;
        window = NULL;

        /*  Quit  SDL subsystems  */
        IMG_Quit();
        SDL_Quit();
    }
    void load();
    void run() {
        ImpTimer fps_time;

        bool quit = false;
        SDL_Event e;

        MainTime.Start();

        while (!quit) {
            fps_time.start();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT)
                    quit = true;

                HandleInput(e);
            }
            SDL_SetRenderDrawColor(screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(screen);

            /*#########################################################*/
                            /* Sovle Display Problem */
            SDL_SetRenderDrawColor(screen, 0, 0, 0, 0);
            SDL_Rect r = {0, 0 , 1280 , 720};
            SDL_RenderFillRect( screen, &r );

            MainTime.Update();

            display();
            /*#########################################################*/
            SDL_RenderPresent(screen);

            /*#########################################################*/
                    /* FPS Problem: Don't Edit or Fix */
            {
            int real_time = fps_time.getTicks();
            int time_each_frame = 1000 / FPS; // ms
            int delay_time = time_each_frame - real_time;
            if (delay_time >= 0)
                SDL_Delay(delay_time);
            }
            /*#########################################################*/
        }
        close();
    }
    void display();
    void HandleInput(SDL_Event e);
};

#endif // GAME_H_
