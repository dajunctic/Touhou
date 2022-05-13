#include "Enemy.h"

Enemy::Enemy(bool is_boss_ ){
    current_status = ENEMY_IDLE;

    time_count = 0;
    current_frame = 0;
    number_frames = 0;
    time_per_frame = 0;
    current_direct = ENEMY_RIGHT;

    time_attack = -1;
    number_frame_attack = 0;

    name = 0;
    x_speed = 0;
    y_speed = 0;
    a = 0;

    is_boss = is_boss_;

    EnemyTime.Start();
}

Enemy::~Enemy(){
    
}

void Enemy::HandleMove(){

    for(auto &x : orbit){
        int current_time = EnemyTime.GetSeconds();
        if(x.st == current_time and EnemyTime.GetFrameTime() == x.step){
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

void Enemy::InitBullet(int start_time, int end_time, int type, int name ){
    plan.push_back({start_time, end_time, type, name});
}

void Enemy::HandleBullet(vector<Bullet> & shot){
    for(auto x : plan){
        if(x.start_time <= EnemyTime.GetSeconds() and EnemyTime.GetSeconds() <= x.end_time){
            MakeBullet(shot, x.type, x.name,  x.start_time, x.end_time);
        }
    }
}

void Enemy::pause()
{
    is_paused = true;
}
void Enemy::resume()
{
    is_paused = false;
}

void Enemy::MakeBullet(vector<Bullet> & shot, int type, int name, int st_time, int en_time){
    if(type == 0){

        // * Cứ 0.5 s 1 vòng tròn đạn bắn ra *//
        if (EnemyTime.CheckSeconds(30)) {
            int tmp = rand()%( 4 - 0 + 1) + 0;
            for(int i = tmp ; i < 360 + tmp ; i += 5){
                Bullet b;

                b.SetPos(center_x, center_y);
                b.SetName(name);
                b.SetAngle(i);
                b.SetSpeed(1.5,1.5);
                b.SetType(b.VECTOR);

                shot.push_back(b);
            }

           ResetAttack();
        }
    }

    if(type == 1){
        // Cứ 0.5 s bắn 1 viên đạn, các viên đạn từ góc 0 tới 180

        if (EnemyTime.CheckSeconds(30)) {
            Bullet b;
            b.SetPos(center_x, center_y);
            b.SetName(name);
            b.SetAngle(18 * (EnemyTime.GetSeconds() - st_time));
            b.SetSpeed(4,4);
            b.SetType(b.VECTOR);
            shot.push_back(b);

            ResetAttack();
        }     
    }
    if(type == 2){
        // Cứ 1 s bắn ra 3 viên đạn xuống dưới (giống grave LOL)

        if (EnemyTime.CheckSeconds(60)){
            for (int i = 75; i <= 115; i += 15) {
                Bullet b;
                b.SetPos(center_x, center_y);
                b.SetName(name);
                b.SetAngle(i);
                b.SetSpeed(3,3);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }
            
            ResetAttack();
        }

    }
    if(type == 3){
        // Cứ 1s bắn ra 4 cặp đạn từ góc 70 tới 110 độ 
        if (EnemyTime.CheckSeconds(60)) {
            for (int i = 70; i <= 110; i += 10) {
                Bullet b;
                b.SetPos(center_x, center_y);
                //b.SetAngle(18 * (EnemyTime.GetSeconds() - st_time));
                b.SetAngle(i);
                b.SetName(name);
                b.SetSpeed(2,2);
                b.SetType(b.VECTOR);
                shot.push_back(b);
                double base = 15;
                double angle_radian = i;
                
                b.SetPos(center_x + sin(angle_radian) * base, center_y - cos(angle_radian) * base);
                b.SetAngle(i);
                b.SetSpeed(2,2);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }

            ResetAttack();
        }
    }
    if(type == 4){
        if (EnemyTime.CheckSeconds(60) and (EnemyTime.GetSeconds() - st_time)%2 == 0) {
            for(int i = 0 ; i < 360 ; i += 12){
                Bullet b;
                b.SetPos(center_x, center_y);
                b.SetName(name);
                b.SetAngle(i);
                b.SetSpeed(1.5,1.5);
                b.SetType(b.VECTOR);
                shot.push_back(b);
                
                double base = 15;
                double angle_radian = i/180.0 * PI;
                    
                b.SetPos(center_x + sin(angle_radian) * base, center_y - cos(angle_radian) * base);
                b.SetAngle(i);
                b.SetSpeed(1.5,1.5);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }


            ResetAttack();
        }

       
    }
}
