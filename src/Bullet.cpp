#include "Bullet.h"

Bullet::Bullet(){
    x = y = 0;
    x_speed = y_speed = 0;
    angle = 90;

    start_point = 0;

    is_delete = false;
}
Bullet::~Bullet(){};
void Bullet::SetRandomAngle(const int& st, const int& en){
    angle = rand() % (en - st + 1) + st;
}
void Bullet::setDelete()
{
    is_delete = true;
}
void Bullet::HandleMove(){
    if(type == VECTOR){
        x += x_speed * cos(angle*PI/180);
        y += y_speed * sin(angle*PI/180);
    }
    if(type == HORIZONTAL_SIN){
        y += 1;
        x = 50 * sin(PI*y/100) + start_point;
    }
    if(type == VERTICAL_SIN){
        x += 1;
        y = 50 * sin(PI*x/100) + start_point;
    }
}

void Bullet::HandleCollision(pair<double,double> p_center, double p_r, SDL_Rect b_rect){
    bool isRadiusCollision = false;
    for(auto &n : RadiusCollision)
        if(n == name) isRadiusCollision = true; 

    if(isRadiusCollision){
        double pX = p_center.fi;
        double pY = p_center.se;
        double pR = p_r;


        double bX = x + b_rect.w / 2;
        double bY = y + b_rect.w / 2; 
        double bR = b_rect.w / 2;

        double d = distance({pX, pY}, {bX, bY});

        if(d < bR + pR){
            is_delete = true;
        }

    }
    else{
        double rotation = (90.0 + angle) / 180 * PI;

        b_rect.x = x;
        b_rect.y = y;

        if(RectInCircle(b_rect, rotation, p_center, p_r)){
            is_delete = true;
        }
    }
}



/* ################### BOMB ##########################*/
Bomb::Bomb()
{
    rotate_angle = 0;
    rotate_speed = 3;

    bomb_time.Start();
    is_used = false;
    is_attack = false;
}
Bomb::~Bomb()
{
    //////
}
void Bomb::load(SDL_Renderer * renderer)
{
    magic_cirle.SetRect(515, 65);
    magic_cirle.Load(renderer, "res/gui/bomb.png");
    
    fire.set(16,5);
    fire.setPos(775, 240);
    fire.load(renderer, "res/gui/animation/fire.png");
    fire.setAlpha(150);

    amulet.Load(renderer, "res/gui/amulet.png");
    amulet.SetRect(800, 325);

    effect.set(6,4, 1);
    effect.setPos(400 , 0);
    effect.load(renderer, "res/gui/animation/bomb2.png");

 //   effect.setAlpha(230);
}
void Bomb::show(SDL_Renderer * renderer)
{
    if(!is_used) return;
    bomb_time.Update();

    if(bomb_time.GetSeconds() == 2)
    {
        is_used = false;
       
        return;
    }

    if(bomb_time.GetSeconds() == 1 and bomb_time.GetFrameTime() == 20)
    {
        is_attack = true;
    }

    if(bomb_time.GetSeconds() >= 1)
    {
        if(effect.isDelete()) return;
        effect.show(renderer);
    }
    else
    {
        rotate_angle += rotate_speed;
        if(rotate_angle > 360) rotate_angle -= 360;

        magic_cirle.RenderAngle(renderer, rotate_angle);
        amulet.Render(renderer);
        fire.show(renderer);
    }
}
void Bomb::use()
{
    is_used = true;
    effect.reset();
}
bool Bomb::isUsed()
{
    return is_used;
}
bool Bomb::isAttack()
{
    return is_attack;
}
void Bomb::setAttack(bool choice)
{
    is_attack = choice;
}
void Bomb::reset()
{
    bomb_time.Reset();
    Bomb();
}