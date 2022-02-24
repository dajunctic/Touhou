#include "GameObject.h"

Object::Object() {
	p_object = NULL;
	rect.x = rect.y = rect.w = rect.h = 0;
}
Object::~Object() {
	Free();
}
void Object::LoadImage(SDL_Renderer * screen, string path) {
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());

	if (load_surface != NULL) {
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL) {
			rect.w = load_surface->w;
			rect.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);
	}
	else{
		string error = "Can't load surface of image \""+ path + "\"";
		throw error;
		return;
	}
	p_object = new_texture;
}
void Object::Render(SDL_Renderer* des, SDL_Rect* clip) {
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };

	SDL_RenderCopy(des, p_object, clip, &renderquad);
}
void Object::Free() {
	if (p_object != NULL) {
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect.w = rect.h = 0;
	}
}