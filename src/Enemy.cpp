#include "Enemy.h"

Enemy::Enemy(){
    current_status = 0;

    time_count = 0;
    current_frame = 0;
    number_frames = 0;
    time_per_frame = 0;

    x_speed = 0;
    y_speed = 0;
    a = 0;

    is_move = true;

    EnemyTime.Start();
}

Enemy::~Enemy(){
    
}

void Enemy::HandleMove(){

    for(auto &x : orbit){
        int current_time = EnemyTime.GetSeconds();
        if(x.st <=  current_time and current_time <= x.en and EnemyTime.CheckSeconds(x.step)){
            x_speed = x.x_speed;
            y_speed = x.y_speed;

            angle = x.angle;
            a = x.a;
        }
    }
    x_speed += a;
    y_speed += a;

    x_speed = max(x_speed, 0.0);
    y_speed = max(y_speed, 0.0);

    x += x_speed * cos(angle*PI/180);
    y += y_speed * sin(angle*PI/180);
}

void Enemy::InitBullet(int start_time, int end_time, int type){
    plan.push_back({start_time, end_time, type});
}

void Enemy::HandleBullet(vector<Bullet> & shot){
    for(auto x : plan){
        if(x.start_time <= EnemyTime.GetSeconds() and EnemyTime.GetSeconds() <= x.end_time){
            MakeBullet(shot, x.type);
        }
    }
}

void Enemy::MakeBullet(vector<Bullet> & shot, int type){
    if(type == 0){

        // * Cứ 0.5 s 1 vòng tròn đạn bắn ra *//
        if (EnemyTime.GetSeconds()%1 == 0 and EnemyTime.CheckSeconds(30)) {
            int tmp = rand()%( 4 - 0 + 1) + 0;
            for(int i = tmp ; i < 360 + tmp ; i += 5){
                Bullet b;

                b.SetPos(center_x, center_y);
                b.SetName(0);
                b.SetAngle(i);
                b.SetSpeed(1.5,1.5);
                b.SetType(b.VECTOR);

                shot.push_back(b);
                
            }
        }
    }

    if(type == 1){

    }
}
