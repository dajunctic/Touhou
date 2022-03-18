#include "Enemy.h"

Enemy::Enemy(){
    current_status = 0;

    time_count = 0;
    current_frame = 0;
    number_frames = 0;
    time_per_frame = 0;

    EnemyTime.Start();
    is_move = true;
}

Enemy::~Enemy(){
    
}

void Enemy::InitBullet(){
    for(int i = 0 ; i < 360 ; i += 6){
        Bullet b;

        b.SetPos(x, y);
        b.SetAngle(i);
        b.SetSpeed(1,1);
        b.SetType(b.VECTOR);

        shot.push_back(b);
    }
}

void Enemy::HandleBullet(SDL_Renderer * screen){
    Object draw;
    draw.LoadImage(screen, "res/img/enemy/b_00.png");
    for(auto &x : shot){
        
        x.HandleMove();
        draw.SetRect(x.GetPos().fi, x.GetPos().se);
        draw.Render(screen);
    }
}