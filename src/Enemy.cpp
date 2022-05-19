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
    necessary = 0;

    EnemyTime.Start();
}

Enemy::~Enemy(){
    
}

void Enemy::HandleMove(){
    if(is_paused) return;

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

    double nx = x + x_speed * cos(angle*PI/180);
    double ny = y + y_speed * sin(angle*PI/180);

    if((x - BOARD_X) * (nx - BOARD_X) <= 0 or (y - BOARD_Y) * (ny - BOARD_Y) <= 0
       or (x - BOARD_LIMITED_X) * (nx - BOARD_LIMITED_X) <= 0 or (y - BOARD_LIMITED_Y) * (ny - BOARD_LIMITED_Y) <= 0 ) 
        necessary ++; 

    x += x_speed * cos(angle*PI/180);
    y += y_speed * sin(angle*PI/180);
}

bool Enemy::checkInBoard()
{
    return (BOARD_X <= x and x <= BOARD_LIMITED_X) and (BOARD_Y <= y and y <= BOARD_LIMITED_Y); 
}

void Enemy::InitBullet(int start_time, int end_time, int type, int name ){
    plan.push_back({start_time, end_time, type, name});
}

void Enemy::HandleBullet(vector<Bullet> & shot, pair<double,double>charcor, int level){
    for(auto x : plan){
        if(x.start_time <= EnemyTime.GetSeconds() and EnemyTime.GetSeconds() <= x.end_time){
            MakeBullet(shot, x.type, x.name,  x.start_time, x.end_time ,charcor, level);
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

void Enemy::MakeBullet(vector<Bullet> & shot, int type, int name, int st_time, int en_time, pair<double,double>charcor,int level)
{
    if(type == 0)
    {

        // * Cứ 0.5 s 1 vòng tròn đạn bắn ra *//
        if (EnemyTime.CheckSeconds(30)) 
        {
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

    if(type == 1)
    {
        // Cứ 0.5 s bắn 1 viên đạn, các viên đạn từ góc 0 tới 180

        if (EnemyTime.CheckSeconds(30)) 
        {
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
    if(type == 2)
    {
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
    //3 vien lien tuc
    if (type == 5) {
        if (level == 0) {
            int truth = 1;
            if (EnemyTime.CheckSeconds(60) and truth >= 0) {
                truth -= 1;
                Bullet b;
                b.SetPos(center_x,center_y);
                b.SetName(name);
                pair<double,double> p(1,0);
                pair<double,double> p2(charcor.first - center_x, charcor.second - center_y);
                double ang = acos(cos(p , p2)) / PI * 180;
                if (charcor.second - center_y < 0 or (charcor.first - center_x == 0 and charcor.second - center_y < 0)) ang = -ang;
                b.SetAngle(ang);
                b.SetSpeed(1.5,1.5);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }
        }
        if (level == 1) {
            int truth = 3;
            if (EnemyTime.CheckSeconds(60) and truth >= 0) {
                truth -= 1;
                Bullet b;
                b.SetPos(center_x,center_y);
                b.SetName(name);
                pair<double,double> p(1,0);
                pair<double,double> p2(charcor.first - center_x, charcor.second - center_y);
                double ang = acos(cos(p , p2)) / PI * 180;
                if (charcor.second - center_y < 0 or (charcor.first - center_x == 0 and charcor.second - center_y < 0)) ang = -ang;
                b.SetAngle(ang);
                b.SetSpeed(1.5,1.5);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }
        }
        if (level == 2) {
            int truth = 3;
            if (EnemyTime.CheckSeconds(60) and truth >= 0) {
                truth -= 1;
                Bullet b;
                b.SetPos(center_x,center_y);
                b.SetName(name);
                pair<double,double> p(1,0);
                pair<double,double> p2(charcor.first - center_x, charcor.second - center_y);
                double ang = acos(cos(p , p2)) / PI * 180;
                if (charcor.second - center_y < 0 or (charcor.first - center_x == 0 and charcor.second - center_y < 0)) ang = -ang;
                b.SetAngle(ang);
                b.SetSpeed(2,2);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }
        }
        if (level == 3) {
            int truth = 6;
            if (EnemyTime.CheckSeconds(30) and truth >= 0) {
                truth -= 1;
                Bullet b;
                b.SetPos(center_x,center_y);
                b.SetName(name);
                pair<double,double> p(1,0);
                pair<double,double> p2(charcor.first - center_x, charcor.second - center_y);
                double ang = acos(cos(p , p2)) / PI * 180;
                if (charcor.second - center_y < 0 or (charcor.first - center_x == 0 and charcor.second - center_y < 0)) ang = -ang;
                b.SetAngle(ang);
                b.SetSpeed(3,3);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }
        }
        ResetAttack();
        }  

    //3s ban 1 vien
    if (type == 6) {
        if (level == 0) {
            if (EnemyTime.CheckSeconds(180)) {
                Bullet b;
                b.SetPos(center_x,center_y);
                b.SetName(name);
                pair<double,double> p(1,0);
                pair<double,double> p2(charcor.first - center_x, charcor.second - center_y);
                double ang = acos(cos(p , p2)) / PI * 180;
                if (charcor.second - center_y < 0 or (charcor.first - center_x == 0 and charcor.second - center_y < 0)) ang = -ang;
                b.SetAngle(ang);
                b.SetSpeed(1,1);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }
        }
        if (level == 1 or level == 2) {
            if (EnemyTime.CheckSeconds(180)) {
                Bullet b;
                b.SetPos(center_x,center_y);
                b.SetName(name);
                pair<double,double> p(1,0);
                pair<double,double> p2(charcor.first - center_x, charcor.second - center_y);
                double ang = acos(cos(p , p2)) / PI * 180;
                if (charcor.second - center_y < 0 or (charcor.first - center_x == 0 and charcor.second - center_y < 0)) ang = -ang;
                b.SetAngle(ang);
                b.SetSpeed(1.5,1.5);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }
        }
        if (level == 3) {
            if (EnemyTime.CheckSeconds(120)) {
                Bullet b;
                b.SetPos(center_x,center_y);
                b.SetName(name);
                pair<double,double> p(1,0);
                pair<double,double> p2(charcor.first - center_x, charcor.second - center_y);
                double ang = acos(cos(p , p2)) / PI * 180;
                if (charcor.second - center_y < 0 or (charcor.first - center_x == 0 and charcor.second - center_y < 0)) ang = -ang;
                b.SetAngle(ang);
                b.SetSpeed(1.5,1.5);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }
        }
        
        ResetAttack();
    }

    //0.5s ban 1 vien
    if (type == 7) {
        if (level == 0) {
            if (EnemyTime.CheckSeconds(60)) {
                Bullet b;
                b.SetPos(center_x,center_y);
                b.SetName(name);
                b.SetAngle(90);
                b.SetSpeed(1,1);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }
        }
        if (level == 1) {
            if (EnemyTime.CheckSeconds(30)) {
                Bullet b;
                b.SetPos(center_x,center_y);
                b.SetName(name);
                b.SetAngle(90);
                b.SetSpeed(1,1);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }
        }
        if (level == 2 or level == 3) {
            if (EnemyTime.CheckSeconds(30)) {
                Bullet b;
                b.SetPos(center_x,center_y);
                b.SetName(name);
                b.SetAngle(90);
                b.SetSpeed(2,2);
                b.SetType(b.VECTOR);
                shot.push_back(b);
            }
        }
        ResetAttack();
    }
    if (type == 8) {
        if (EnemyTime.CheckSeconds(60)) {
            Bullet b;
            b.SetPos(center_x,center_y);
            b.SetName(name);
            pair<double,double> p(1,0);
            pair<double,double> p2(charcor.first - center_x, charcor.second - center_y);
            double ang = acos(cos(p , p2)) / PI * 180;
            if (charcor.second - center_y < 0 or (charcor.first - center_x == 0 and charcor.second - center_y < 0)) ang = -ang;
            b.SetAngle(ang);
            b.SetSpeed(10,10);
            b.SetType(b.VECTOR);
            shot.push_back(b);
        }
    }

    if (type == 9) {
        if (EnemyTime.CheckSeconds(60)) {
            Bullet b;
            b.SetPos(center_x,center_y);
            b.SetName(name);
            b.SetAngle(75);
            b.SetSpeed(2,2);
            b.SetType(b.VECTOR);
            shot.push_back(b);
        }
    }
    if (type == 10) {
        if (EnemyTime.CheckSeconds(60)) {
            Bullet b;
            b.SetPos(center_x,center_y);
            b.SetName(name);
            b.SetAngle(60);
            b.SetSpeed(2,2);
            b.SetType(b.VECTOR);
            shot.push_back(b);
        }
    }
    if (type == 11) {
        if (EnemyTime.CheckSeconds(60)) {
            Bullet b;
            b.SetPos(center_x,center_y);
            b.SetName(name);
            b.SetAngle(45);
            b.SetSpeed(2,2);
            b.SetType(b.VECTOR);
            shot.push_back(b);
        }
    }
    if (type == 12) {
        if (EnemyTime.CheckSeconds(60)) {
            Bullet b;
            b.SetPos(center_x,center_y);
            b.SetName(name);
            b.SetAngle(30);
            b.SetSpeed(2,2);
            b.SetType(b.VECTOR);
            shot.push_back(b);
        }
    }
    if (type == 13) {
        if (EnemyTime.CheckSeconds(60)) {
            Bullet b;
            b.SetPos(center_x,center_y);
            b.SetName(name);
            b.SetAngle(15);
            b.SetSpeed(2,2);
            b.SetType(b.VECTOR);
            shot.push_back(b);
        }
    }


    if (type == 14) {
        if (EnemyTime.CheckSeconds(60)) {
            Bullet b;
            b.SetPos(center_x,center_y);
            b.SetName(name);
            b.SetAngle(165);
            b.SetSpeed(2,2);
            b.SetType(b.VECTOR);
            shot.push_back(b);
        }
    }
    if (type == 15) {
        if (EnemyTime.CheckSeconds(60)) {
            Bullet b;
            b.SetPos(center_x,center_y);
            b.SetName(name);
            b.SetAngle(150);
            b.SetSpeed(2,2);
            b.SetType(b.VECTOR);
            shot.push_back(b);
        }
    }
    if (type == 16) {
        if (EnemyTime.CheckSeconds(60)) {
            Bullet b;
            b.SetPos(center_x,center_y);
            b.SetName(name);
            b.SetAngle(135);
            b.SetSpeed(2,2);
            b.SetType(b.VECTOR);
            shot.push_back(b);
        }
    }
    if (type == 17) {
        if (EnemyTime.CheckSeconds(60)) {
            Bullet b;
            b.SetPos(center_x,center_y);
            b.SetName(name);
            b.SetAngle(120);
            b.SetSpeed(2,2);
            b.SetType(b.VECTOR);
            shot.push_back(b);
        }
    }
    if (type == 18) {
        if (EnemyTime.CheckSeconds(60)) {
            Bullet b;
            b.SetPos(center_x,center_y);
            b.SetName(name);
            b.SetAngle(105);
            b.SetSpeed(2,2);
            b.SetType(b.VECTOR);
            shot.push_back(b);
        }
    }
    
    if (type == 19) {
        if (level == 0) {
            if (EnemyTime.CheckSeconds(120)) {
                    Bullet b;
                    b.SetPos(center_x,center_y);
                    b.SetName(name);
                    pair<double,double> p(1,0);
                    pair<double,double> p2(charcor.first - center_x, charcor.second - center_y);
                    double ang = acos(cos(p , p2)) / PI * 180;
                    if (charcor.second - center_y < 0 or (charcor.first - center_x == 0 and charcor.second - center_y < 0)) ang = -ang;
                    b.SetAngle(ang);
                    b.SetSpeed(1.5,1.5);
                    b.SetType(b.VECTOR);
                    shot.push_back(b);
            }
        }
        if (level == 1 or level == 2) {
            if (EnemyTime.CheckSeconds(120)) {
                    Bullet b;
                    b.SetPos(center_x,center_y);
                    b.SetName(name);
                    pair<double,double> p(1,0);
                    pair<double,double> p2(charcor.first - center_x, charcor.second - center_y);
                    double ang = acos(cos(p , p2)) / PI * 180;
                    if (charcor.second - center_y < 0 or (charcor.first - center_x == 0 and charcor.second - center_y < 0)) ang = -ang;
                    b.SetAngle(ang);
                    b.SetSpeed(2,2);
                    b.SetType(b.VECTOR);
                    shot.push_back(b);
            }
        }
        if (level == 3) {
            if (EnemyTime.CheckSeconds(90)) {
                    Bullet b;
                    b.SetPos(center_x,center_y);
                    b.SetName(name);
                    pair<double,double> p(1,0);
                    pair<double,double> p2(charcor.first - center_x, charcor.second - center_y);
                    double ang = acos(cos(p , p2)) / PI * 180;
                    if (charcor.second - center_y < 0 or (charcor.first - center_x == 0 and charcor.second - center_y < 0)) ang = -ang;
                    b.SetAngle(ang);
                    b.SetSpeed(2,2);
                    b.SetType(b.VECTOR);
                    Bullet b2,b3;
                    b2.SetPos(center_x,center_y);
                    b2.SetName(name);
                    b2.SetAngle(ang + 10);
                    b2.SetSpeed(2,2);
                    b2.SetType(b2.VECTOR);
                    b3.SetPos(center_x,center_y);
                    b3.SetName(name);
                    b3.SetAngle(ang - 10);
                    b3.SetSpeed(2,2);
                    b3.SetType(b3.VECTOR);
                    shot.push_back(b);
                    shot.push_back(b2);
                    shot.push_back(b3);
            }
        }
        ResetAttack();
    }

}
