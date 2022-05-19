#if !defined(GAME_TEXT_H)
#define GAME_TEXT_H

#include "Touhou.h"

class Text{
private:
    string text;

    int size;
    string font_path;

    TTF_Font * font = NULL;
    SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;

    SDL_Rect srcRect;
	SDL_Rect desRect;

    SDL_Color color;

    int limited_width;
    int line_space = 30;
    vector<string> line;

    double x, y;

public:
    Text();
    ~Text();

    void setSize(int);
    void setFont(string);
    void setColor(SDL_Renderer * renderer, Uint8 r, Uint8 b, Uint8 g, Uint8 a = 255);
    void setPos(double, double);
    void setText(SDL_Renderer *, string);
    void setAlpha(Uint8 a);
    double getPosX();
    double getPosY();
    void setRender(SDL_Renderer *);
    void show(SDL_Renderer *);

    SDL_Rect getRect();

    void setLineSpace(int line_space);
    void setParagraph(int limited_width);
    void showParagraph(SDL_Renderer *, string display = "left");
};

/*##############################  Dialogue ######################### */
class Dialogue{
private:
    string text;
    string current_text;
    Text speech;

    double current_alpha;
    double text_speed;

    SDL_Rect size;    

    bool finished;

    // left center right //
    string display; 
public:
    Dialogue();
    ~Dialogue();

    void setSize(int x, int y, int w, int h);
    void setText(SDL_Renderer *, string);
    void setTextSpeed(double );
    void setDisplay(string);
    void load(SDL_Renderer *);
    void show(SDL_Renderer *);
    void finish();
    bool isFinished();
    void reset();
};
#endif // GAME_TEXT_H
