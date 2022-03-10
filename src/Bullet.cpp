#include "Bullet.h"

Bullet::Bullet(){
    x = y = 0;
    x_speed = y_speed = 0;
    angle = 90;

    start_point = 0;
}
Bullet::~Bullet(){};
void Bullet::SetRandomAngle(const int& st, const int& en){
    angle = rand() % (en - st + 1) + st;
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
