#include "Touhou.h"
#include "GameObject.h"
#include "Character.h"
#include "ImpTimer.h"

void init();
void close();
void load();
void display();

void InputKeyboard(SDL_Event e);

multiset<int> Key;

Character Hakurei;
Object Test;

/* Main Process*/
int main(int argc, char* args[]) {
	ImpTimer fps_timer;

	try {
		init();
		load();
	} catch(const char* msg) {
		cerr << msg << endl;
		return 0;
	} catch (string error) {
		cerr << error << endl;
		return 0;
	}

	bool quit = false;
	SDL_Event e;

	while (!quit) {
		fps_timer.start();
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
			InputKeyboard(e);
		}
		SDL_SetRenderDrawColor(screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(screen);

		display();
		
		SDL_RenderPresent(screen);

		int real_time = fps_timer.getTicks();
		int time_each_frame = 1000 / FPS; // ms
		int delay_time = time_each_frame - real_time;
		if (delay_time >= 0)
			SDL_Delay(delay_time);
	}
	close();
	return 0;
}
void init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw "Can't SDL_Init"; return;
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
void load() {
	Test.LoadImage(screen, "res/img/hakurei.png");
//	cout << "Image Size: " << Test.GetRect().w << " " << Test.GetRect().h << endl;

	Hakurei.Set(8 , 5);
	Hakurei.SetPos(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT - 200);
	Hakurei.Load(screen, "hakurei");
	
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
void display() {
//	Test.Render(screen);
	
	Hakurei.Update();
	Hakurei.Show(screen);

}
void InputKeyboard(SDL_Event e){
	if(e.type == SDL_KEYDOWN){

		switch (e.key.keysym.sym){
		case SDLK_RIGHT:
			Key.insert(K_RIGHT);
			Hakurei.SetMove(true);
			Hakurei.Move(1 , 0);
			break;
		case SDLK_LEFT:
			Key.insert(K_LEFT);
			Hakurei.SetMove(true);
			Hakurei.Move(-1 , 0);
			break;
		case SDLK_UP:
			Key.insert(K_UP);
			Hakurei.SetMove(true);
			Hakurei.Move(0 , -1);
			break;
		case SDLK_DOWN:
			Key.insert(K_DOWN);
			Hakurei.SetMove(true);
			Hakurei.Move(0 , 1);
			break;

		
		default:
			break;
		}
		
	} 
	if(e.type == SDL_KEYUP){
		switch (e.key.keysym.sym){
		case SDLK_RIGHT:
			Key.erase(K_RIGHT);
			if (Key.empty())
				Hakurei.SetMove(false);
			break;
		case SDLK_LEFT:
			Key.erase(K_LEFT);
			if (Key.empty())
				Hakurei.SetMove(false);
			break;
		case SDLK_UP:
			Key.erase(K_UP);
			if (Key.empty())
				Hakurei.SetMove(false);
			break;
		case SDLK_DOWN:
			Key.erase(K_DOWN);
			if (Key.empty())
				Hakurei.SetMove(false);
			break;

		default:
			break;
		}
	}
}