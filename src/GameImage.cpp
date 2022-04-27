#include "GameImage.h"

Image::Image() 
{
	p_image = NULL;
	rect.x = rect.y = rect.w = rect.h = 0;
}
Image::~Image() 
{
	if (p_image != NULL) 
	{
		SDL_DestroyTexture(p_image);
		p_image = NULL;
		rect.w = rect.h = 0;
	}
}
void Image::Load(SDL_Renderer * screen, string path) 
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());

	if (load_surface != NULL) 
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL) 
		{
			rect.w = load_surface->w;
			rect.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);
	}
	else
	{
		string error = "Can't load surface of image \""+ path + "\"";
		throw error;
		return;
	}
	p_image = new_texture;
	SetBlendMode(SDL_BLENDMODE_BLEND);
}
void Image::SetBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(p_image, blending);
}
void Image::SetAlpha(Uint8 alpha) 
{
	SDL_SetTextureAlphaMod(p_image, alpha);
}
void Image::Render(SDL_Renderer* screen, SDL_Rect* clip) 
{
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };

	SDL_RenderCopy(screen, p_image, clip, &renderquad);
}
void Image::RenderAngle(SDL_Renderer* screen, double angle, SDL_Rect* clip) 
{
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };
	SDL_Point center = {rect.w / 2, rect.h / 2};

	SDL_RenderCopyEx( screen, p_image, NULL, &renderquad, angle , &center, SDL_FLIP_NONE );
}
void Image::Free()
{
	if (p_image != NULL) 
	{
		SDL_DestroyTexture(p_image);
		p_image = NULL;
		rect.w = rect.h = 0;
	}
}


/* ##################### Animation  ########################*/
Animation::Animation()
{
	type = 0;

	count_frame = -1;
	number_frame = 1;
	current_frame = -1;
	time_frame = 1;

	x = y = 0;

	repeat = -1;
	is_delete = false; 
}
Animation::~Animation()
{
	// Don;t know :) //
}
void Animation::setType(int type)
{
	this->type = type;
}
void Animation::set(int number_frame, int time_frame, int repeat)
{
	this->number_frame = number_frame;
	this->time_frame = time_frame;
	this->repeat = repeat + 1;
}
void Animation::setPos(double x, double y)
{
	this->x = x;
	this->y = y;
}
bool Animation::isDelete() 
{
	return is_delete;
}
void Animation::load(SDL_Renderer * renderer, string path)
{
	if(type == 0)
	{
		single_image.Load(renderer, path);
		single_image.SetBlendMode(SDL_BLENDMODE_BLEND);
	}
	else
	{
		// Handle this part "sau" // 
		return;
	}
}
void Animation::update()
{
	count_frame ++;
	count_frame %= time_frame;

	if(count_frame == 0)
	{
		current_frame ++;
		current_frame %= number_frame;

		if(current_frame == 0)
		{
			if(repeat != -1){
				repeat --;

				if(repeat == 0)
				{
					is_delete = true;
					return;
				}

			}
		}
	}
}
void Animation::setAlpha(Uint8 a)
{	
	if(type == 0)
	{
		single_image.SetAlpha(a);
	}
}
void Animation::show(SDL_Renderer * renderer, Image * img)
{
	update();
	if(is_delete) return;

	if(img == NULL)
	{
		if(type == 0)
		{
			SDL_Texture* texture = single_image.GetImage();
			SDL_Rect rect = single_image.GetRect();
			rect.w = rect.w / number_frame;
			rect.x = current_frame * rect.w;

			SDL_Rect renderquad = { int(x) , int(y) , rect.w , rect.h };
			SDL_RenderCopy(renderer, texture, &rect, &renderquad);
		}
		else{
			// Handle this part "sau" //
			return;
		}
	}
	else
	{
		if(type == 0)
		{
			SDL_Texture* texture = img->GetImage();
			SDL_Rect rect = img->GetRect();
			rect.w = rect.w / number_frame;
			rect.x = current_frame * rect.w;

			SDL_Rect renderquad = { int(x) , int(y) , rect.w , rect.h };
			SDL_RenderCopy(renderer, texture, &rect, &renderquad);
		}
		else{
			// Handle this part "sau" //
			return;
		}
	}
}
void Animation::reset()
{
	count_frame = -1;
	current_frame = -1;
	repeat = 2;

	is_delete = false; 
}