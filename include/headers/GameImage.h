#ifndef GAME_IMAGE_H_
#define GAME_IMAGE_H_

#include "Touhou.h"

class Image {
public:
	Image();
	~Image();

	void SetRect(const int& x, const int& y) { rect.x = x, rect.y = y;}
	SDL_Rect GetRect() const { return rect; }
	SDL_Texture* GetImage() const { return p_image; }

	void Load(SDL_Renderer * screen, string path);
	void Render(SDL_Renderer* des, SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* p_image;
	SDL_Rect rect;
};

#endif // !GAME_IMAGE_H_