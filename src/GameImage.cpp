#include "GameImage.h"

Image::Image() {
	p_image = NULL;
	rect.x = rect.y = rect.w = rect.h = 0;
}
Image::~Image() {
	Free();
}
void Image::Load(SDL_Renderer * screen, string path) {
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
	p_image = new_texture;
}
void Image::Render(SDL_Renderer* screen, SDL_Rect* clip) {
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };

	SDL_RenderCopy(screen, p_image, clip, &renderquad);
}
void Image::RenderAngle(SDL_Renderer* screen, double angle, SDL_Rect* clip) {
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };
	SDL_Point center = {rect.w / 2, rect.h / 2};

//	SDL_RenderCopy(des, p_image, clip, &renderquad);
	SDL_RenderCopyEx( screen, p_image, NULL, &renderquad, angle , &center, SDL_FLIP_NONE );
}

void Image::Free() {
	if (p_image != NULL) {
		SDL_DestroyTexture(p_image);
		p_image = NULL;
		rect.w = rect.h = 0;
	}
}