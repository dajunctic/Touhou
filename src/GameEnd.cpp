#include "GameEnd.h"

End::End()
{
    script1 = "Because this is just an exercise for the final exam, our team would like to stop developing this game.";
    script2 = "If anyone has made it through all the levels, thanks for coming to the end with us.";
}
End::~End()
{

}
void End::load(SDL_Renderer * renderer)
{
    postscript1.setSize(150 ,100 ,1280 - 150 * 2, SCREEN_HEIGHT - 500);
    postscript1.load(renderer);
    postscript1.setTextSpeed(0.4);
    postscript1.setDisplay("center");
    postscript1.setText(renderer, script1);

    postscript2.setSize(150 ,200 ,1280 - 150 * 2, SCREEN_HEIGHT - 500);
    postscript2.load(renderer);
    postscript2.setTextSpeed(0.4);
    postscript2.setDisplay("center");
    postscript2.setText(renderer, script2);

    back.setSize(20);
    back.setText(renderer, "[ Space or Enter to back the menu ]");
    back.setPos((SCREEN_WIDTH - back.getRect().w) / 2, 680);

    thanks.Load(renderer, "res/gui/thanks.png");
    thanks.SetRect((SCREEN_WIDTH - thanks.GetRect().w) / 2, 250);

    bg = Mix_LoadMUS("res/bgm/Thanks.mp3");
    thankyou = Mix_LoadWAV("res/sfx/thanks.wav");
}
void End::show(SDL_Renderer * renderer)
{
    if(!isBgm )
    {
        isBgm = true;
        Mix_PlayMusic(bg, -1);
    }
    postscript1.show(renderer);
    if(postscript1.isFinished())
    {
        postscript2.show(renderer);
    }
    
    if(postscript2.isFinished())
    {
        if(!isThank)
        {
            isThank = true;
            Mix_PlayChannel(-1, thankyou, 0);
        }
        thanks.Render(renderer);
        back.show(renderer);
        isBack = true;
    }
}
void End::handleInput(SDL_Event e, int * SCENE)
{
    if(e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_RETURN:
            if(isBack)
            {
                *SCENE = 1; // MENU
                isBack = false;
            }
            break;
        case SDLK_SPACE:
            if(isBack)
            {
                *SCENE = 1; // MENU
                isBack = false;
            }
            break;
        
        default:
            break;
        }
    }
}