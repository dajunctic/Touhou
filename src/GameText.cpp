#include "GameText.h"

Text::Text()
{
    text = "You are using SDL_Text!";
    size = 30;

    font_path = "fonts/mgenplus-2pp-regular.ttf";

    font = TTF_OpenFont(font_path.c_str(), size);

    srcRect = {0 , 0 , 0 , 0};

    color.r = 255;
    color.b = 255;
    color.g = 255;
    color.a = 255;

    limited_width = 600;

}

Text::~Text()
{
    /* I don't know which datas will be left */
}

void Text::setSize(int size)
{
    this->size = size;
    this->font = TTF_OpenFont(this->font_path.c_str(), this->size);
}
void Text::setFont(string font_path)
{
    this->font_path = font_path;
    this->font = TTF_OpenFont(this->font_path.c_str(), this->size);
}

void Text::setColor(SDL_Renderer * renderer, Uint8 r, Uint8 b, Uint8 g, Uint8 a)
{
    color.r = r;
    color.b = b;
    color.g = g;
    color.a = a;
//    setRender(renderer);
}

void Text::setPos(double x, double y)
{
    this->x = x;
    this->y = y;
    desRect.x = int(x);
    desRect.y = int(y);
}

void Text::setText(SDL_Renderer* renderer, string text)
{
    this->text = text;
    TTF_SizeText(font, text.c_str(), &srcRect.w, &srcRect.h);
//    setRender(renderer);
}

void Text::setRender(SDL_Renderer * renderer)
{
    TTF_SizeText(font, text.c_str(), &srcRect.w, &srcRect.h);

    desRect.w = srcRect.w;
	desRect.h = srcRect.h;

    SDL_Surface * surface = TTF_RenderText_Blended(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, color.a);
}

void Text::show(SDL_Renderer * renderer)
{
    desRect.x = int(x);
    desRect.y = int(y);
    setRender(renderer);
    SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
    
    SDL_DestroyTexture(texture);

}
void Text::setAlpha(Uint8 a)
{
    color.a = a;
//    SDL_SetTextureAlphaMod(texture, a);
}
double Text::getPosX()
{
    return x;
}
double Text::getPosY()
{
    return y;
}
SDL_Rect Text::getRect()
{
    return srcRect;
}

void Text::setLineSpace(int line_space_)
{
    line_space = line_space_;
}
void Text::setParagraph(int limited_width_)
{
    limited_width = limited_width_;
    line.clear();

    string current_line = "";
    for(int i = 0 ; i < text.length(); i++)
    {
        current_line += text[i];

        TTF_SizeText(font, current_line.c_str(), &srcRect.w, &srcRect.h);


        if(srcRect.w > limited_width)
        {   
            while(current_line.back() != ' ')
            {
                current_line.pop_back();
                i--;
            }
            line.push_back(current_line);
            current_line = "";
        }
    }
    line.push_back(current_line);
}
void Text::showParagraph(SDL_Renderer * renderer, string display)
{
    int x = desRect.x;
    int y = desRect.y;
    for(int i = 0 ; i < line.size() ; i++)
    {
        setText(renderer, line[i]);
        if(display == "left")
        {
            setPos(x, y + line_space * i);
        }
        if(display == "center")
        {
            setPos((SCREEN_WIDTH - srcRect.w) / 2, y + line_space * i);
        }
        if(display == "right")
        {
            setPos(SCREEN_WIDTH - srcRect.w, y + line_space * i);
        }
        show(renderer);
    }

    desRect.x = x;
    desRect.y = y;
}


/*##############################  Dialogue ######################### */
Dialogue::Dialogue()
{
    current_text = "";
    text = "This is a speech!";

    text_speed = 0.3;
    current_alpha = -text_speed;

    size.w = 1080;

    finished = false;
    display = "left";
}
Dialogue::~Dialogue()
{
 // Do nothing
}
void Dialogue::setSize(int x, int y, int w, int h)
{
    size.x = x;
    size.y = y;
    size.w = w;
    size.h = h;
}
void Dialogue::setText(SDL_Renderer * renderer, string text)
{
    this->text = text;
    speech.setText(renderer, text);
    speech.setParagraph(size.w);
    current_text = "";
    current_alpha = -text_speed;
    finished = false;
}
void Dialogue::setTextSpeed(double speed /* 0 <= speed <= 1 */)
{
    text_speed = speed;
}
void Dialogue::setDisplay(string display)
{
    this->display = display;
}
void Dialogue::load(SDL_Renderer * renderer)
{
    speech.setSize(25);
    speech.setPos(size.x, size.y);
    speech.setLineSpace(40);
    
    speech.setText(renderer, text);
    speech.setParagraph(size.w);
}
void Dialogue::show(SDL_Renderer * renderer)
{
    if(finished == false)
    {
        current_alpha += text_speed;
        current_alpha = min(current_alpha, double(text.size()));
        current_text = "";
        for(int i = 0 ; i < current_alpha ; i++) 
        {
            current_text += text[i];
        }  
        if(current_alpha >= double(text.size()))
        {
            finished = true;
        }

        speech.setText(renderer, current_text);
        speech.setParagraph(size.w);
    }
    else
    {
        speech.setText(renderer, text);
        speech.setParagraph(size.w);
    }
    
    speech.showParagraph(renderer,display);
}
void Dialogue::finish()
{
    finished = true;
}
bool Dialogue::isFinished()
{
    return finished;
}
void Dialogue::reset()
{
    current_text = "";
    current_alpha = -text_speed;
    finished = false;
}