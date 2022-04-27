#include "PowerShard.h"

PowerShard::PowerShard()
{
    v = 2.4;
    a = -0.02;

    is_delete = false;

    angle = 90;
    speed = 10;
}
void PowerShard::set(int type, double x, double y)
{
    this->type = type;
    this->x = x;
    this->y = y;
    
}
int PowerShard::getType()
{
    return type;
}
SDL_Rect PowerShard::getRect()
{
    rect.x = x;
    rect.y = y;
    return rect;
}
void PowerShard::setDelete()
{
    is_delete = true;
}
bool PowerShard::isDelete()
{
    return is_delete;
}
void PowerShard::load(Image * img)
{
    rect.w = img->GetRect().w;
    rect.h = img->GetRect().h;
}
void PowerShard::show(SDL_Renderer * renderer, Image * img, pair<double,double> cha)
{
    if(type >= 4)
    {

        double cX = x + rect.w / 2.0;
        double cY = y + rect.h / 2.0;

        pair<double,double> v = {cha.first - cX, cha.second - cY};

        angle = acos(cos(v, {1, 0})) / PI * 180.0;
        if(v.se < 0 or (v.fi == 0 and v.se < 0)) angle = -angle ;

        speed = min(10.0 , distance({cX, cY}, cha));

        x += speed * cos(angle / 180.0 * PI);
        y += speed * sin(angle / 180.0 * PI);
    }
    else
    {
        v += a;
        y -= v;
        angle = 0;
    }

    if(y > 720) is_delete = true;

    img->SetRect(x, y);
    img->RenderAngle(renderer,angle);
}