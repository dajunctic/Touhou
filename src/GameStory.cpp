#include "GameStory.h"

Story::Story()
{
    current_script = 0;
    next_script = false;

    bg = {"light_moon", "deep_forest", "mystery", "default", "room", "temple", "small_light"};
    for(auto x : bg)
    {
        string path = "res/img/bg/" + x + ".jpg";
        bgMap[x] = path;
    }

    scripts = 
    {
        // 0000
        {
            "noone",
            "Somewhere deep in the forest..."
        },
        // 0001
        {
            "??????",
            "Did you hear the news? Looks like we're about to have a horrible-sounding blood sacrifice ever!"
        },
        // 0002
        {
            "######",
            "I just heard about it too, our lord have found the ancient magic circle to connect this world with hell."
        },
        // 0003
        {
            "??????",
            "Hell!..."
        },
        // 0004
        {
            "######",
            "Right! Are you feeling your own blood boiling?"
        },
        // 0005
        {
            "??????",
            "So it's a sign..."
        },
        // 0006
        {
            "??????",
            "Hahaha hahaha! So is our time coming? Damn onmyouji, when we get our strength back from hell we won't have to run around like this anymore."
        },
        // 0007
        {
            "######",
            "That's what we all want..."
        },
        // 0008
        {
            "noone",
            "The creepy laughter resounded in a corner of the forest in the middle of the night, causing a commotion around the surroundings."
        },
        // 0009
        {
            "noone",
            "The crows also suddenly squawked with horror..."
        },

        // 0010 
        {
            "noone",
            "Light is the core thing that gives birth to all things, from single-celled bodies to evolve into multi-cells and then into creatures like our world."
        },
        // 0011
        {
            "noone",
            "However, according to an ancient note, there existed a world covered by a long, seemingly endless night that swallowed all that existed in it."
        },
        // 0012
        {   
            "noone",
            "Strange things happen that we can't explain, can't even imagine, maybe it's a miracle."
        },
        // 0013
        {   
            "noone",
            "In the deep and cold darkness, mutant forms thrive and evolve constantly..."
        },
        // 0014
        {
            "Hakurei",
            "Phew phew!"
        },
        // 0015
        {
            "Hakurei",
            "Ummm! I have dreamed about the stories grandma told again."
        },
        // 0016
        {
            "Hakurei",
            "It happen regularly these days! Is something bad about to happen?"
        },
        // 0017
        {
            "Hakurei",
            "Oh! I forget to introduce myself!"
        },
        // 0018
        {
            "Hakurei",
            "I am Hakurei Reimu - an onmyouji passed down through many generations."
        },
        // 0019
        {
            "Hakurei",
            "And I am also a very cute girl!"
        },
        // 0020
        {
            "Hakurei",
            "Um! Time to check around this area, too tired, wanna a hug! UwU..."
        },
        // 0021
        {
            "noone",
            "Looks like tonight is going to be another peaceful night! But suddenly there was a call."
        },
        // 0022
        {
            "Someone",
            "Hahurei! Hakurei!"
        },
        // 0023
        {
            "Hakurei",
            "Alice!"
        },
        // 0024
        {
            "Hakurei",
            "You look rushed"
        },
        // 0025
        {
            "Alice",
            "Phew phew, we are getting some troubles."
        },
        // 0026
        {
            "Alice",
            "There was a prophetic talisman that was burned, when I entered the temple it was already ashes."
        },
        // 0027
        {
            "Alice",
            " Perhaps recently some dark power has appeared, and this power seems to be terrible."
        },
        // 0028
        {
            "Alice",
            "We need to investigate this matter urgently."
        },
        // 0029
        {
            "noone",
            "Alice lit a talisman and chanted some magical spells, the small lights lit up and seemed to be leading the two girls somewhere."
        },
        // 0030
        {
            "noone",
            "The two followed the small lights that led the way."
        },
        // 0031
        {
            "??????",
            "Kaka, why are these two cute girls hanging around here."
        },
        // 0032
        {
            "Alice",
            "Be careful, Hakurei!"
        },
        // 0033
        {
            "Hakurei",
            "Ready to fight!!!"
        }
    };
    
}
Story::~Story()
{

}
void Story::load(SDL_Renderer * renderer)
{
    textbox.Load(renderer, "res/gui/textbox.png");
    textbox.SetBlendMode(SDL_BLENDMODE_BLEND);
    textbox.SetAlpha(255);

    message_line.Load(renderer, "res/gui/message_line.png");
    message_line.SetRect((SCREEN_WIDTH - message_line.GetRect().w) / 2, 520);
    name.setSize(26);
    name.setFont("fonts/NotoSansCJKjp-Bold.otf");
    name.setText(renderer, scripts[current_script].first);

    transition.set(6, 45);
    transition.load(renderer, "res/gui/animation/transition.png");
    transition.setPos(transition_x , transition_y);


    dialogue.setSize(150 ,565 ,1280 - 150 * 2, SCREEN_HEIGHT - 500);
    dialogue.load(renderer);
    dialogue.setTextSpeed(0.4);
    dialogue.setText(renderer, scripts[current_script].second);


    /* character */
    rh.Load(renderer, "res/img/char/rh7.png");
    rh_happy.Load(renderer, "res/img/char/rh3.png");
    rh_surprise.Load(renderer, "res/img/char/rh9.png");
    rh_blink.Load(renderer, "res/img/char/rh5.png");
    rh_shy.Load(renderer, "res/img/char/rh2.png");

    am.Load(renderer, "res/img/char/am9.png");
    am_sad.Load(renderer, "res/img/char/am2.png");
    am_blink.Load(renderer, "res/img/char/am3.png");
}
void Story::show(SDL_Renderer * renderer)
{
    showBackground(renderer);
    showCharacter(renderer);

    textbox.Render(renderer);
    dialogue.show(renderer);

    if(dialogue.isFinished())
    {
        transition_y += transition_speed;
        if(transition_y == 660 or transition_y == 640)
        {
            transition_speed = -transition_speed;
        }

        transition.setPos(transition_x, transition_y);
        transition.show(renderer);

        if(next_script)
        {
            next_script = false;
            if(scripts[current_script].first != "noone")
            {
                dialogue.setText(renderer,"\"" + scripts[current_script].second + "\"");
            }
            else
            {
                dialogue.setText(renderer, scripts[current_script].second);
            }
        }
    }

    /* Name */
    if(scripts[current_script].first != "noone")
    {
        message_line.Render(renderer);
        name.setText(renderer, scripts[current_script].first);
        name.setPos((SCREEN_WIDTH - name.getRect().w) / 2 , 500);
        name.show(renderer);
    } 
}
void Story::showBackground(SDL_Renderer * renderer)
{   
    if(loadBg)
    {
        if(0 == current_script)
        {
            bgImg.Load(renderer, bgMap["deep_forest"]);
        }
        if(10 == current_script)
        {
            bgImg.Load(renderer, bgMap["mystery"]);
        }
        if(11 == current_script)
        {
            bgImg.Load(renderer, bgMap["default"]);
        }
        if(14 == current_script)
        {
            bgImg.Load(renderer, bgMap["room"]);
        }
        if(21 == current_script)
        {
            bgImg.Load(renderer, bgMap["temple"]);
        }
        if(30 == current_script)
        {
            bgImg.Load(renderer, bgMap["small_light"]);
        }
        if(31 == current_script)
        {
            bgImg.Load(renderer, bgMap["light_moon"]);
        }

        loadBg = false;
    }

    bgImg.Render(renderer);
}
void Story::showCharacter(SDL_Renderer * renderer)
{
    if(14 <= current_script and current_script <= 16)
    {
        SDL_Rect r = rh_shy.GetRect();
        rh_shy.SetRect(getPosX("c-left", r),getPosY(r));
        rh_shy.Render(renderer);
    }

    if(current_script == 17)
    {
        SDL_Rect r = rh_surprise.GetRect();
        rh_surprise.SetRect(getPosX("c-left", r),getPosY(r));
        rh_surprise.Render(renderer);
    }
    if(current_script == 18)
    {
        SDL_Rect r = rh.GetRect();
        rh.SetRect(getPosX("c-left", r),getPosY(r));
        rh.Render(renderer);
    }
    if(current_script == 19)
    {
        SDL_Rect r = rh_blink.GetRect();
        rh_blink.SetRect(getPosX("c-left", r),getPosY(r));
        rh_blink.Render(renderer);
    }
    if(current_script == 20)
    {
        SDL_Rect r = rh.GetRect();
        rh.SetRect(getPosX("c-left", r),getPosY(r));
        rh.Render(renderer);
    }
    if(current_script == 23)
    {
        SDL_Rect r = rh.GetRect();
        rh.SetRect(getPosX("left", r),getPosY(r));
        rh.Render(renderer);
    }
    if(current_script == 23)
    {
        SDL_Rect r = rh_surprise.GetRect();
        rh_surprise.SetRect(getPosX("left", r),getPosY(r));
        rh_surprise.Render(renderer);
    }
    if(current_script == 24)
    {
        SDL_Rect r = rh_shy.GetRect();
        rh_shy.SetRect(getPosX("left", r),getPosY(r));
        rh_shy.Render(renderer);
    }
    if(current_script == 25)
    {
        SDL_Rect r = rh_shy.GetRect();
        rh_shy.SetRect(getPosX("left", r),getPosY(r));
        rh_shy.Render(renderer);

        SDL_Rect r2 = am_sad.GetRect();
        am_sad.SetRect(getPosX("right", r2),getPosY(r2));
        am_sad.Render(renderer);
    }
    if(current_script == 26 or current_script == 27 or current_script == 28)
    {
        SDL_Rect r = am.GetRect();
        am.SetRect(getPosX("center", r),getPosY(r));
        am.Render(renderer);
    }
    if(current_script == 32)
    {
        SDL_Rect r = am.GetRect();
        am.SetRect(getPosX("center", r),getPosY(r));
        am.Render(renderer);
    }
    if(current_script == 33)
    {
        SDL_Rect r = rh.GetRect();
        rh.SetRect(getPosX("center", r),getPosY(r));
        rh.Render(renderer);
    }
}

void Story::handleInput(SDL_Event e, int * scene)
{
    if(e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_RETURN:
                if(dialogue.isFinished())
                {
                    current_script ++;
                    if(current_script ==  scripts.size())
                    {
                        *scene = 2; // MAIN
                    }
                    next_script = true;
                    loadBg = true;
                }
                else
                {
                    dialogue.finish();
                }
                break;
            case SDLK_SPACE:
                if(dialogue.isFinished())
                {
                    current_script ++;
                    if(current_script ==  scripts.size())
                    {
                        *scene = 2; // MAIN
                    }
                    next_script = true;
                    loadBg = true;
                }
                else
                {
                    dialogue.finish();
                }

                break;

            default:
                break;
        }
    }
}

int Story::getPosX(string type, SDL_Rect rect)
{
    int x;
    if(type == "left")
        x = 0;
    
    if(type == "c-left")
        x =  SCREEN_WIDTH/2 - rect.w;
    
    if(type == "center")
        x =  (SCREEN_WIDTH - rect.w) / 2;

    if(type == "c-right")
        x = SCREEN_WIDTH / 2;

    if(type == "right")
        x = SCREEN_WIDTH - rect.w;
    
    return x;
}
int Story::getPosY(SDL_Rect rect)
{
    return SCREEN_HEIGHT - rect.h;
}