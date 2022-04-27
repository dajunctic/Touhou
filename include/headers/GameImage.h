#ifndef GAME_IMAGE_H_
#define GAME_IMAGE_H_

#include "Touhou.h"

class Image {
private:
	SDL_Texture* p_image;
	SDL_Rect rect;

public:
	Image();
	~Image();
	void Free();

	void SetRect(const int& x, const int& y) { rect.x = x, rect.y = y;}
	SDL_Rect GetRect() const { return rect; }
	SDL_Texture* GetImage() const { return p_image; }

	void Load(SDL_Renderer * screen, string path);
	void SetBlendMode(SDL_BlendMode blending);
	void SetAlpha(Uint8 alpha);
	void Render(SDL_Renderer* screen, SDL_Rect* clip = NULL);
	void RenderAngle(SDL_Renderer* screen, double angle, SDL_Rect* clip = NULL);
};

class Animation {
private:
	int type; // load a single image or a multiple-image

	int count_frame;
	int number_frame;
	int current_frame;
	int time_frame; // 60 / x  FPS

	Image single_image;
	Image multiple_image[20];

	double x, y;

	int repeat; // number of repeat animation 
	int is_delete;

public:
	Animation();
	~Animation();
	void setType(int);
	void set(int the_frame_number, int time_per_frame, int repeat = -1);
	void setPos(double, double);
	bool isDelete();
	void load(SDL_Renderer *, string);
	void update();
	void setAlpha(Uint8 a);
	void show(SDL_Renderer * , Image * img = NULL);
	void reset();
};

#endif // !GAME_IMAGE_H_