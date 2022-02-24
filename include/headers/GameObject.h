#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "Touhou.h"

class Object {
public:
	Object();
	~Object();

	void SetRect(const int& x, const int& y) { rect.x = x, rect.y = y;}
	SDL_Rect GetRect() const { return rect; }
	SDL_Texture* GetObject() const { return p_object; }

	void LoadImage(SDL_Renderer * screen, string path);
	void Render(SDL_Renderer* des, SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* p_object;
	SDL_Rect rect;
};

#endif // !GAME_OBJECT_H_