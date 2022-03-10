#include "Touhou.h"
#include "GameObject.h"
#include "Character.h"
#include "Bullet.h"
#include "ImpTimer.h"

/*#########################################################*/
					/* Declare Function */
void init();
void close();
void load();
void display();
void HandleInput(SDL_Event e);
multiset<int> Key;
/*#########################################################*/
/*#########################################################*/
					/* Game Variable */
GameTime MainTime;
Character Hakurei;

/*#########################################################*/
/*#########################################################*/
					/* Solve functions*/
int main(int argc, char* args[]) {
	ImpTimer fps_timer;

	init();
	load();

	bool quit = false;
	SDL_Event e;

	MainTime.Start();

	while (!quit) {
		fps_timer.start();
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
		int real_time = fps_timer.getTicks();
		int time_each_frame = 1000 / FPS; // ms
		int delay_time = time_each_frame - real_time;
		if (delay_time >= 0)
			SDL_Delay(delay_time);
		/*#########################################################*/
	}
	close();
	return 0;
}
void init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout <<  "Can't Init SDL";
		exit(0);
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		throw "Warning: Linear texture filtering not enabled!" ;

	window = SDL_CreateWindow("Touhou", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
		throw "Can't create window!";
	else {
		screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (screen == NULL) {
			throw "Can't create Screen by creating render!";
			return;
		}
		else {
			SDL_SetRenderDrawColor(screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

			int pngImgFlags = IMG_INIT_PNG;
			int jpgImgFlags = IMG_INIT_JPG;

			if (!(IMG_Init(pngImgFlags) & pngImgFlags) or !(IMG_Init(jpgImgFlags) & jpgImgFlags)){
				throw "SDL_Image Setting Failed";
				return;
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
void load() {

	/* Main Character */
	Hakurei.Set(8 , 5);
	Hakurei.SetPos(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT - 200);
	Hakurei.Load(screen, "hakurei");
}

void display() {

	Hakurei.Update();
	Hakurei.Show(screen);
}
void HandleInput(SDL_Event e){
	if(e.type == SDL_KEYDOWN){

		switch (e.key.keysym.sym){
		case SDLK_RIGHT:
			Key.insert(K_RIGHT);
			Hakurei.SetMove(true);
			Hakurei.SetStatus(Hakurei.RIGHT);
			Hakurei.Move();

			
			break;
		case SDLK_LEFT:
			Key.insert(K_LEFT);
			Hakurei.SetMove(true);
			Hakurei.SetStatus(Hakurei.LEFT);
			Hakurei.Move();

			
			break;
		case SDLK_UP:
			Key.insert(K_UP);
			Hakurei.SetMove(true);
			Hakurei.SetStatus(Hakurei.UP);
			Hakurei.Move();
			break;
		case SDLK_DOWN:
			Key.insert(K_DOWN);
			Hakurei.SetMove(true);
			Hakurei.SetStatus(Hakurei.DOWN);
			Hakurei.Move();
			break;

		case SDLK_z:
			Hakurei.Shoot(true);
			break;
		
		default:
			break;
		}
		
	} 
	if(e.type == SDL_KEYUP){
		switch (e.key.keysym.sym){
		case SDLK_RIGHT:
			Key.erase(K_RIGHT);
			break;
		case SDLK_LEFT:
			Key.erase(K_LEFT);
			break;
		case SDLK_UP:
			Key.erase(K_UP);
			break;
		case SDLK_DOWN:
			Key.erase(K_DOWN);
			break;

		case SDLK_z:
			Hakurei.Shoot(false);
			break;

		default:
			break;
		}
		if (Key.empty()){
			Hakurei.SetMove(false);
			Hakurei.SetStatus(Hakurei.IDLE);
		}
		else{
			Hakurei.SetStatus(*Key.begin() + 1);
			Hakurei.Move();
		}
	}
}