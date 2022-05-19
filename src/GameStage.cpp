#include "GameStage.h"

void Stage::Load(SDL_Renderer * renderer)
{
    stage_time.Start();

    // Level Choice //
    level_theme.Load(renderer, "res/gui/theme_difficulty.png");
    level_img.Load(renderer, "res/gui/difficulty.png");
    select.Load(renderer, "res/gui/select_.png");

    esc.setColor(renderer, 255 , 255, 255);
    esc.setSize(25);
    esc.setFont("fonts/segoeprb.ttf");
    esc.setText(renderer, "ESC to return Home");
    esc.setPos(SCREEN_WIDTH / 2 - esc.getRect().w / 2, 670);

    // game status //
    pause.Load(renderer, "res/gui/pause.png");
    die.Load(renderer, "res/gui/die.png");
    win.Load(renderer, "res/gui/win.png");

    stage_name.setSize(45);
    stage_name.setPos(250, SCREEN_HEIGHT / 2 - 100);
    stage_name.setText(renderer, "STAGE 1");

    stage_content.setSize(25);
    stage_content.setPos(620, 720);
    stage_content.setText(renderer, "The mysterious blood sacrifice.");

    // Notification //
    noti_img.Load(renderer, "res/gui/notification.png");
    noti_img.SetRect(noti_x, noti_y);
    noti_text.setSize(20);
    noti_text.setColor(renderer, 255, 67, 53);
    noti_text.setFont("fonts/segoeprb.ttf");
    noti_text.setPos(noti_x + 70, noti_y + 20);
    noti_text.setText(renderer, "Unlock a new episode!");
    noti_time.Start();
    noti = Mix_LoadWAV("res/sfx/notification.wav");

    // Story //
    story.load(renderer);
    // End // 
    game_end.load(renderer);

     /* Load Game Image */{   
        GameBg.Load(renderer, "res/img/bg/theme_00.jpg");
        GameBg.SetRect(0, 0);
        StageBg.Load(renderer, "res/img/bg/chapter_01.png");
        // Load bullet Image
        for(int i = 0 ; i < 12 ; i++){
            string id = to_string(i);
            if(i < 10) id = '0' + id;
            string path = "res/img/bullet/b_" +  id + ".png";
            shot_img[i].Load(renderer, path);
        }

        life_text.setSize(35);
        life_text.setPos(280, 47);
        life_text.setText(renderer, to_string(life));

        explode_text.setSize(35);
        explode_text.setPos(280, 135);
        explode_text.setText(renderer, to_string(explode));

        score_text.setSize(35);
        score_text.setPos(100, 600);
        string score_str = to_string(score);
        int tmp  = score_str.size();
        for(int i = 0 ; i < 6 - tmp ; i++) score_str = '0' + score_str;
        score_text.setText(renderer, score_str);

        hakurei_animation.set(14, 6);
        hakurei_animation.load(renderer, "res/gui/animation/hakurei.png");
        hakurei_animation.setPos(60, 230);

        bomb.load(renderer);
        bomb_sfx = Mix_LoadWAV("res/sfx/explosion_3.wav");


        for(int i = 0 ; i < 6 ; i++)
        {
            string path = "res/img/char/power_0" + to_string(i) + ".png";
            powershard_img[i].Load(renderer, path);
        }
    }
    /* Load Character */
    {
        Hakurei.Set(8 , 10);
        Hakurei.SetPos((SCREEN_WIDTH + BOARD_X) / 2 - 16, SCREEN_HEIGHT - 200);
        Hakurei.Load(renderer, "hakurei");
    }
    /* Load Enemy */
    {
        explosion_img.Load(renderer, "res/gui/animation/explosion.png");

        for(int i = 0 ; i < 4 ; i++)
        {
            string path = "res/img/enemy/enemy_";
            string tmp = to_string(i);
            if(i < 10) tmp = '0' + tmp;

            enemy_img[i][0].Load(renderer, path + tmp + ".png");
            enemy_img[i][1].Load(renderer, path + tmp + "_left.png");
            enemy_img[i][2].Load(renderer, path + tmp + "_right.png");
            enemy_img[i][3].Load(renderer, path + tmp + "_attack_left.png");
            enemy_img[i][4].Load(renderer, path + tmp + "_attack_right.png");
        }
    }
    /* Load Boss */
    {
        for(int i = 1 ; i < 2 ; i++)
        {
            string path = "res/img/boss/boss_";
            string tmp = to_string(i);
            if(i < 10) tmp = '0' + tmp;

            boss_img[i][0].Load(renderer, path + tmp + "_idle.png");
            boss_img[i][1].Load(renderer, path + tmp + "_left.png");
            boss_img[i][2].Load(renderer, path + tmp + "_right.png");
            boss_img[i][3].Load(renderer, path + tmp + "_attack_left.png");
            boss_img[i][4].Load(renderer, path + tmp + "_attack_right.png");
        }

    }
    createEnemy();
    bgm = Mix_LoadMUS("res/bgm/ShanghaiScarletTeahouse.mp3");

    dead_sfx = Mix_LoadWAV("res/sfx/dead.wav");
    enemy_dead = Mix_LoadWAV("res/sfx/enemy_dead.wav");
}

void Stage::createEnemy()
{
    enemy.clear();
    shot.clear();

    /* ################            1ST ENEMY WAY           ####################*/
    Enemy FstWaveR[6];
    Enemy FstWaveL[6];
    for (int i = 0; i < 6; i++) {
        int nameR = (i % 2) ? 2 : 0;
        int nameL = (i % 2) ? 2 : 0;

        FstWaveR[i].SetPos(1100 - 232 * (i % 2), -60);
        FstWaveR[i].Set(4, 10);
        FstWaveR[i].SetName(nameR);
        FstWaveR[i].Load(enemy_img[nameR]);

        FstWaveL[i].SetPos(440 + 200 * (i % 2) , -60);
        FstWaveL[i].Set(4, 10);
        FstWaveL[i].SetName(nameL);
        FstWaveL[i].Load(enemy_img[nameL]);
    }
    for (int i = 0; i < 6; i++) {
        FstWaveR[i].SetOrbit(2+i,0,{2,2},0,90);
        FstWaveL[i].SetOrbit(2+i,0,{2,2},0,90);
    }

    if (level >= HARD) 
    {
        for (int i = 1; i < 6; i++) {
            FstWaveR[i].InitBullet(2+i,3+i,19-i,11);
            FstWaveL[i].InitBullet(2+i,3+i,8+i,11);
        }
    }
    for (int i = 0; i < 6; i++) {
        enemy.push_back(FstWaveR[i]);
        enemy.push_back(FstWaveL[i]);
    }

/* ################            2ND ENEMY WAY           ####################*/
    Enemy SecondWaveR[6];
    Enemy SecondWaveL[6];
    for (int i = 0; i < 6; i++) 
    {
        SecondWaveR[i].SetPos(1320, 160);
        SecondWaveR[i].Set(4, 10, 2);
        SecondWaveR[i].SetName(1);
        SecondWaveR[i].Load(enemy_img[1]);
        SecondWaveR[i].SetFitAttackFrame(11.0, 0.0);
        SecondWaveL[i].SetPos(270, 80);
        SecondWaveL[i].Set(4, 10, 2);
        SecondWaveL[i].SetName(1);
        SecondWaveL[i].Load(enemy_img[1]);
        SecondWaveL[i].SetFitAttackFrame(11.0, 0.0);
    }    
    for (int i = 0; i < 6; i++) 
    {
        SecondWaveR[i].SetOrbit(10+i,0,{4,4},0,180);
        SecondWaveL[i].SetOrbit(10+i,0,{4,4},0,0);
    }
    for (int i = 0; i < 6; i += 3) 
    {
        SecondWaveR[i].InitBullet(10+i,13+i,7,11);
        SecondWaveL[i].InitBullet(10+i,13+i,7,11);
    }
    if (level == LEGENDARY) 
    {
        SecondWaveR[2].InitBullet(12,13,8,11);
        SecondWaveL[4].InitBullet(14,15,8,11);
    }
    for (int i = 0; i < 6; i++) 
    {
        enemy.push_back(SecondWaveR[i]);
        enemy.push_back(SecondWaveL[i]);
    }
    
/* ################            3RD ENEMY WAY           ####################*/
    Enemy ThirdWaveR[8];
    Enemy ThirdWaveL[8];
    for (int i = 0; i < 4; i++) 
    {
        ThirdWaveR[i].SetPos(280, 0);
        ThirdWaveR[i].Set(4, 10, 2);
        ThirdWaveR[i].SetName(1);
        ThirdWaveR[i].Load(enemy_img[1]);
        ThirdWaveR[i].SetFitAttackFrame(11.0, 0.0);
        ThirdWaveL[i].SetPos(1320,0);
        ThirdWaveL[i].Set(4, 10, 2);
        ThirdWaveL[i].SetName(1);
        ThirdWaveL[i].Load(enemy_img[1]);
        ThirdWaveL[i].SetFitAttackFrame(11.0, 0.0);
    }
    for (int i = 4; i < 8; i++) 
    {
        ThirdWaveR[i].SetPos(280, 100);
        ThirdWaveR[i].Set(4, 10, 2);
        ThirdWaveR[i].SetName(1);
        ThirdWaveR[i].Load(enemy_img[1]);
        ThirdWaveR[i].SetFitAttackFrame(11.0, 0.0);
        ThirdWaveL[i].SetPos(1320,100);
        ThirdWaveL[i].Set(4, 10, 2);
        ThirdWaveL[i].SetName(1);
        ThirdWaveL[i].Load(enemy_img[1]);
        ThirdWaveL[i].SetFitAttackFrame(11.0, 0.0);
    }
    for (int i = 0; i < 4; i++) 
    {
        ThirdWaveR[i].SetOrbit(19+i,0,{2,2},0,30);
        ThirdWaveR[i].InitBullet(20+i,22+i,5,11);
        ThirdWaveL[i].SetOrbit(19+i,0,{2,2},0,150);
        ThirdWaveL[i].InitBullet(20+i,22+i,5,11);
    }
    for (int i = 4; i < 8; i++) 
    {
        ThirdWaveR[i].SetOrbit(15+i,30,{2,2},0,30);
        ThirdWaveR[i].InitBullet(16+i,18+i,5,11);
        ThirdWaveL[i].SetOrbit(15+i,30,{2,2},0,150);
        ThirdWaveL[i].InitBullet(16+i,18+i,5,11);
    }
    for (int i = 0; i < 8; i++) 
    {
        enemy.push_back(ThirdWaveR[i]);
        enemy.push_back(ThirdWaveL[i]);
    }

/* ################            4TH ENEMY WAY           ####################*/
    Enemy FourthWave[10];
    FourthWave[0].SetPos(380,-140);
    FourthWave[1].SetPos(470,-100);
    FourthWave[2].SetPos(560,-120);
    FourthWave[3].SetPos(650,-180);
    FourthWave[4].SetPos(740,-200); 
    FourthWave[5].SetPos(830,-220);
    FourthWave[6].SetPos(920,-170);
    FourthWave[7].SetPos(1010,-140);
    FourthWave[8].SetPos(1100,-130);
    FourthWave[9].SetPos(1190,-210);
    for (int i = 0; i < 10; i++) {
        FourthWave[i].Set(4, 10, 2);
        FourthWave[i].SetName(1);
        FourthWave[i].Load(enemy_img[1]);
        FourthWave[i].SetFitAttackFrame(11.0, 0.0);
        FourthWave[i].InitBullet(25,34,6,11);
    }
    FourthWave[0].SetOrbit(23,0,{3,3},-0.01,90);
    FourthWave[3].SetOrbit(23,30,{3,3},-0.01,90);
    FourthWave[8].SetOrbit(24,0,{3,3},-0.01,90);
    FourthWave[5].SetOrbit(24,30,{3,3},-0.01,90);
    FourthWave[9].SetOrbit(25,0,{3,3},-0.01,90);
    FourthWave[1].SetOrbit(25,30,{3,3},-0.01,90);
    FourthWave[6].SetOrbit(26,0,{3,3},-0.01,90);
    FourthWave[7].SetOrbit(26,30,{3,3},-0.01,90);
    FourthWave[4].SetOrbit(27,0,{3,3},-0.01,90);
    FourthWave[2].SetOrbit(27,30,{3,3},-0.01,90);
    FourthWave[0].SetOrbit(37,0,{0,0},0.01,270);
    FourthWave[3].SetOrbit(37,30,{0,0},0.01,270);
    FourthWave[8].SetOrbit(38,0,{0,0},0.01,270);
    FourthWave[5].SetOrbit(38,30,{0,0},0.01,270);
    FourthWave[9].SetOrbit(39,0,{0,0},0.01,270);
    FourthWave[1].SetOrbit(39,30,{0,0},0.01,270);
    FourthWave[6].SetOrbit(40,0,{0,0},0.01,270);
    FourthWave[7].SetOrbit(40,30,{0,0},0.01,270);
    FourthWave[4].SetOrbit(41,0,{0,0},0.01,270);
    FourthWave[2].SetOrbit(41,30,{0,0},0.01,270);
    for (int i = 0; i < 10; i++) {
        enemy.push_back(FourthWave[i]);
    }
   

/* ################            5TH ENEMY WAY           ####################*/    Enemy FifthWave[12];
    for (int i = 0; i < 12; i++) {
        FifthWave[i].SetPos(370+ i*80, -60);
        FifthWave[i].Set(4, 10, 2);
        FifthWave[i].SetName(1);
        FifthWave[i].Load(enemy_img[1]);
        FifthWave[i].SetFitAttackFrame(11.0, 0.0);
    }
    FifthWave[0].SetOrbit(32,0,{4,4},0,90);
    FifthWave[1].SetOrbit(32,15,{4,4},0,90);
    FifthWave[2].SetOrbit(32,30,{4,4},0,90);
    FifthWave[3].SetOrbit(32,45,{4,4},0,90);
    FifthWave[4].SetOrbit(33,0,{4,4},0,90);
    FifthWave[5].SetOrbit(33,15,{4,4},0,90);
    FifthWave[6].SetOrbit(33,30,{4,4},0,90);
    FifthWave[7].SetOrbit(33,45,{4,4},0,90);
    FifthWave[8].SetOrbit(34,0,{4,4},0,90);
    FifthWave[9].SetOrbit(34,15,{4,4},0,90);
    FifthWave[10].SetOrbit(34,30,{4,4},0,90);
    FifthWave[11].SetOrbit(34,45,{4,4},0,90);
    for (int i = 0; i < 12; i++) enemy.push_back(FifthWave[i]);
    
        /*After boss*/

        // Real //

        /* BOSS */
        /*
        {
            boss.SetPos(840 - 20 , 200);
            boss.Set(4, 8, 7);
            boss.SetName(1);
            boss.Load(boss_img[1]);
            boss.SetFitAttackFrame(0.0, 25.0);
            boss.InitBullet(0 , 2, 0, 11);   
            // boss.SetOrbit(2,0,{2,2},-0.01, 90);
            // boss.SetOrbit(5, 0,{2,2}, 0, -90);
            // boss.SetOrbit(7, 0,{0,0}, 0, 90);
            // // Hinh elip //
            // int tmp = 8, tmp2 = 0;
            // for(int j = -90 ; j < 270 ; j+=5)
            // {
            //     boss.SetOrbit(tmp, tmp2, {2.5,1}, 0,  j );
            //     tmp2 += 5;
            //     if(tmp2 >= 60){
            //         tmp++;
            //         tmp2 = 0;
            //     }
            // }
            // boss.SetOrbit(tmp, tmp2, {0,0}, 0, 180);
            enemy.push_back(boss);
        }*/

//    Enemy Test2;

// int truth = 1;

// for(int i = 700 ; i <= 900 ; i += 200)
// {
//     truth -= 1;
//     Enemy Test;

//     Test.SetPos(i , 200);
//     Test.Set(4, 10);
//     Test.SetName(3);
//     Test.Load(enemy_img[1]);
//     //Test.SetFitAttackFrame(11.0, 0.0);
//     Test.InitBullet(0 , 2, 0, 11);  

//     /*
//     Test.SetOrbit(2,0,{2,2},-0.01, 90);

//     Test.SetOrbit(5, 0,{2,2}, 0, -90);
//     Test.SetOrbit(7, 0,{0,0}, 0, 90);

//     // Hinh elip //
//     int tmp = 8, tmp2 = 0;
//     for(int j = -90 ; j < 270 ; j+=5)
//     {
//         Test.SetOrbit(tmp, tmp2, {2.5,1}, 0,  j + 180 * truth);
//         tmp2 += 5;
//         if(tmp2 >= 60){
//             tmp++;
//             tmp2 = 0;
//         }
//     }
//     Test.SetOrbit(tmp, tmp2, {0,0}, 0, 180);
//     */

//     enemy.push_back(Test);
// }

    // Real //
    Enemy boss = Enemy(true);
    /* BOSS */
    boss.SetPos(840 - 20 , 200);
    boss.Set(4, 8, 7);
    boss.SetName(1);
    boss.Load(boss_img[1]);
    boss.SetFitAttackFrame(0.0, 25.0);
    boss.InitBullet(0 , 2, 0, 11);   

    // boss.SetOrbit(2,0,{2,2},-0.01, 90);

    // boss.SetOrbit(5, 0,{2,2}, 0, -90);
    // boss.SetOrbit(7, 0,{0,0}, 0, 90);

    // // Hinh elip //
    // int tmp = 8, tmp2 = 0;
    // for(int j = -90 ; j < 270 ; j+=5)
    // {
    //     boss.SetOrbit(tmp, tmp2, {2.5,1}, 0,  j );
    //     tmp2 += 5;
    //     if(tmp2 >= 60){
    //         tmp++;
    //         tmp2 = 0;
    //     }
    // }
    // boss.SetOrbit(tmp, tmp2, {0,0}, 0, 180);

    enemy.push_back(boss);
    
}

void Stage::createEnemyViaTime()
{
    //1st Wave
    Enemy FirstWaveAB;
    Enemy FirstWaveAB2;
    FirstWaveAB.SetPos(600, 200);
    FirstWaveAB.Set(4, 10, 2);
    FirstWaveAB.SetName(1);
    FirstWaveAB.Load(enemy_img[1]);
    FirstWaveAB.SetFitAttackFrame(11.0, 0.0);
    FirstWaveAB.InitBullet(3,63,19,11);
    FirstWaveAB2.SetPos(970, 200);
    FirstWaveAB2.Set(4, 10, 2);
    FirstWaveAB2.SetName(1);
    FirstWaveAB2.Load(enemy_img[1]);
    FirstWaveAB2.SetFitAttackFrame(11.0, 0.0);
    FirstWaveAB2.InitBullet(3,63,19,11);

    if (stage_time.GetSeconds() == 3 and stage_time.CheckSeconds(60)) 
    {
        enemy.push_back(FirstWaveAB); 
        enemy.push_back(FirstWaveAB2);
    }
}

void Stage::Show(SDL_Renderer * renderer)
{
    if(scene == LEVEL_CHOICE){
        level_theme.Render(renderer);
        select.SetRect((SCREEN_WIDTH - select.GetRect().w)/2, 220 + level * 75);
        select.Render(renderer);

        level_img.Render(renderer);
        
        esc.show(renderer);
    }
    if(scene == STORY)
    {
        story.show(renderer);
    }
    if(scene == END)
    {
        game_end.show(renderer);
    }
    if(scene == MAIN)
    {
        if(!isBgm)
        {
            isBgm = true;
            Mix_PlayMusic(bgm, -1);
        }
        GameBg.Render(renderer);

        bomb.show(renderer);
        Hakurei.Show(renderer);

        if(current_display == INTRO)
        {
            if(stage_name.getPosX() <= 810 - stage_name.getRect().w / 2)
            {
                stage_name.setPos(stage_name.getPosX() + 5, stage_name.getPosY());
            }
            else
            {
                stage_content_blur = true;
            }

            if(stage_content.getPosY() >= 360 - stage_content.getRect().h / 2)
            {
                stage_content.setPos(stage_content.getPosX(), stage_content.getPosY() - 4);
            }

            if(stage_content_blur)
            {
                stage_content_alpha --;
            }

            if(stage_content_alpha == -1)
            {
                current_display = PROCESS;
                
            }
            else
            {
                stage_name.setAlpha(stage_content_alpha);
                stage_content.setAlpha(stage_content_alpha);
                stage_name.show(renderer);
                stage_content.show(renderer);
            }
        }

        if(current_display == PROCESS)
        {
            stage_time.Update();

            Hakurei.HandleBullet(enemy, &score);
            /* Display Enemy */

            createEnemyViaTime();
            HandleEnemy(renderer);
            HandleShot(renderer);
        }

        /* Show Another */
        if(is_paused) pause.Render(renderer);
        if(is_loser) die.Render(renderer);
        if(is_winner){
            win.Render(renderer);

            if(is_noti)
            {
                if(noti_y == -65) Mix_PlayChannel(-1, noti, 0);

                if(noti_y < limit_noti_y)
                {
                    noti_y += 5;
                }
                else{
                    noti_time.Update();
                    if(noti_x < limit_noti_x and noti_time.GetSeconds() >= 3) noti_x += 10;
                }

                noti_img.SetRect(noti_x, noti_y);
                noti_img.Render(renderer);

                noti_text.setPos(noti_x + 70, noti_y + 15);
                noti_text.show(renderer);
            }
            
        }

        StageBg.Render(renderer);
        life_text.setText(renderer, to_string(life));
        life_text.show(renderer);
        explode_text.setText(renderer, to_string(explode));
        explode_text.show(renderer);

        string score_str = to_string(score);
        int tmp  = score_str.size();
        for(int i = 0 ; i < 6 - tmp ; i++) score_str = '0' + score_str;
        score_text.setText(renderer, score_str);
        score_text.show(renderer);

        hakurei_animation.show(renderer);
    }
}

void Stage::setScene(int scene_)
{
    scene = scene_;
}
void Stage::setNotification(bool value)
{
    is_noti = value;
}

void Stage::HandleEnemy(SDL_Renderer * renderer)
{   

    for(auto &x : enemy){
        if(bomb.isAttack() and x.checkInBoard())
            x.minusHealhPoint(bomb_power);

        if(RectInRect(x.GetRect(), Hakurei.getRect())){
            if(!is_loser and !Hakurei.isRessurect()){
                HandleCharacter(renderer);
                return;
            }
        }
    }
    
    // Take Score
    for(auto &x : shards)
    {
        if(RectInRect(x.getRect(), Hakurei.getRect()))
        {
            if(x.getType() == 4)  
                score += 1;
            else 
                score += 100;
            x.setDelete();
        }
    }

    if(bomb.isAttack())
    {
        bomb.setAttack(false);
        explode_text.setText(renderer, to_string(explode));

        // take score

        for(auto &x : shot)
        {
            PowerShard element;
            element.set(4, x.GetPos().fi, x.GetPos().se);
            element.load(&powershard_img[4]);
            
            shards.push_back(element);
            x.setDelete();
        }
    }

    vector<Enemy> erased_enemy;
    for(auto &x : enemy)
    {
        if (x.isDie())
        {
            // add score
            score += x.getDefaultHP() * 10;
            Mix_PlayChannel(-1, enemy_dead , 0);

            // make explosion
            Animation component;
            component.set(6, 5, 1);
            component.setPos(x.GetCenterPos().fi - explosion_img.GetRect().w/12, x.GetCenterPos().se - explosion_img.GetRect().h/2);
            explosion.push_back(component);

            // make powershard

            int x1 = x.GetCenterPos().fi - explosion_img.GetRect().w/12;
            int y1 = x.GetCenterPos().se - explosion_img.GetRect().h/2;

            int x2 = x.GetCenterPos().fi + explosion_img.GetRect().w/12;
            int y2 = x.GetCenterPos().se + explosion_img.GetRect().h/2;

            int num = 2;
            if(x.IsBoss()) num = 10;
            
            for(int i = 0 ; i < num ; i++)
            {
                int type = rand() % 4 + 0; // 0 1 2 3

                double psX = rand() % (x2 - x1 + 1) + x1;
                double psY = rand() % (y2 - y1 + 1) + y1;

                PowerShard element;
                element.set(type, psX, psY);
                element.load(&powershard_img[type]);

                shards.push_back(element);

            }

            continue;
        }  
        if(x.necessary >= 2) continue;

        erased_enemy.push_back(x);
    } 
    enemy = erased_enemy;

    // show enemy
    for(auto &x : enemy)
    {
        if(x.IsBoss())  
            x.Show(renderer, boss_img[x.GetName()][x.GetStatus()]);
        else 
            x.Show(renderer, enemy_img[x.GetName()][x.GetStatus()]);
        
        x.HandleMove();
        x.HandleBullet(shot, Hakurei.GetCenter(), level);

    }

    // show powershard
    vector<PowerShard> erased_shards;
    for(auto &x : shards)
    {
        if(x.isDelete()) continue;
        erased_shards.push_back(x);
    }
    shards = erased_shards;

    for(auto &x : shards)  x.show(renderer, &powershard_img[x.getType()], Hakurei.GetCenter());

    if(shards.empty() and enemy.empty())  is_winner = true;
    

    // show explosion
    vector<Animation> erased_explosion;
    for(auto &x : explosion)
    {
        if(x.isDelete()) continue;
        erased_explosion.push_back(x);
    }
    explosion = erased_explosion;

    for(auto &x : explosion)  x.show(renderer, &explosion_img);
    
}

void Stage::HandleCharacter(SDL_Renderer * renderer)
{
    Hakurei.Die(true);
            
    Mix_PlayChannel(-1, dead_sfx, 0);

    life --;
    life_text.setText(renderer, to_string(life));

    if(life > 0)
        Hakurei.setRessurect(true);
    else{
        is_loser = true;
        for(auto &x : enemy) x.pause();
        for(auto &x : shot) x.pause();
    }
}

void Stage::HandleShot(SDL_Renderer * renderer)
{
    // Show
    for(auto &x : shot)
    {
        x.HandleMove();
        int w = shot_img[x.GetName()].GetRect().w;
        int h = shot_img[x.GetName()].GetRect().h;

        shot_img[x.GetName()].SetRect(x.GetPos().fi - w / 2, x.GetPos().se - h / 2);
        shot_img[x.GetName()].RenderAngle(renderer, 90 + x.GetAngle());
    }

     // Handle collision with player and border

    vector<Bullet> tmp;

    for(int i = 0 ; i < shot.size() ; i++)
    {
        if(shot[i].IsDelete()) continue; // use bomb or boss die

        Bullet * s = &shot[i];
        if(!Hakurei.IsDie() and !Hakurei.isRessurect())
        {
            s->HandleCollision(Hakurei.GetCenter(), Hakurei.GetRadius(), shot_img[s->GetName()].GetRect());
        }

        if(s->IsDelete()) HandleCharacter(renderer);

        int w = shot_img[s->GetName()].GetRect().w;
        int h = shot_img[s->GetName()].GetRect().h;
        int x = s->GetPos().fi;
        int y = s->GetPos().se;

        if (s->IsDelete() or x + w <= BOARD_X or y + h <= BOARD_Y  or x >= BOARD_LIMITED_X or y >= BOARD_LIMITED_Y) 
        {
            continue;
        }
        
        tmp.push_back(*s);
    } 

    shot = tmp;
}

void Stage::HandleInput(SDL_Event e,int * SCENE)
{
    if(scene == STORY)
    {
        story.handleInput(e, &scene);
    }
    if(scene == END)
    {
        game_end.handleInput(e, SCENE);
    }
    if(scene == LEVEL_CHOICE)
    {
        if(e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_UP:
                    level += (TOTAL_DIFFICULTY - 1);
                    level %= TOTAL_DIFFICULTY;
                    break;

                case SDLK_DOWN:
                    level ++;
                    level %= TOTAL_DIFFICULTY;
                    break;

                case SDLK_ESCAPE:
                    *SCENE = 1; // MENU
                    break;
                
                case SDLK_RETURN:
                    scene = STORY;
                    Mix_HaltMusic();
                    break;
                    
                default:
                    break;
            }
        }
    }
    if(scene == MAIN)
    {
        if(e.type == SDL_KEYDOWN)
        {
            if(is_loser or is_winner) return;
            switch (e.key.keysym.sym)
            {
                case SDLK_RIGHT:
                    Key.insert(K_RIGHT);
                    Hakurei.SetMove(true);
                    Hakurei.SetStatus(Hakurei.RIGHT);
                    Hakurei.Move();

                    break;
                case SDLK_LEFT:
                    Key.insert(K_LEFT);
                    Hakurei.SetMove(true);
                    Hakurei.SetStatus(Hakurei.LEFT);
                    Hakurei.Move();

                        
                    break;
                case SDLK_UP:

                    Key.insert(K_UP);
                    Hakurei.SetMove(true);
                    Hakurei.SetStatus(Hakurei.UP);
                    Hakurei.Move();
                    break;
                case SDLK_DOWN:

                    Key.insert(K_DOWN);
                    Hakurei.SetMove(true);
                    Hakurei.SetStatus(Hakurei.DOWN);
                    Hakurei.Move();
                    break;

                case SDLK_z:
                    Hakurei.Shoot(true);
                    break;

                case SDLK_x:
                    if(!bomb.isUsed() and explode)
                    {
                        bomb.reset();
                        bomb.use();
                        explode --;
                        Mix_PlayChannel(-1, bomb_sfx, 0);
                    }
                    break;

                case SDLK_LSHIFT:
                    Hakurei.PressShift(true);
                    break;
                
                    
                default:
                    break;
            }   
        } 
        if(e.type == SDL_KEYUP)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_RIGHT:
                    Key.erase(K_RIGHT);
                    break;
                case SDLK_LEFT:
                    Key.erase(K_LEFT);
                    break;
                case SDLK_UP:
                    Key.erase(K_UP);
                    break;
                case SDLK_DOWN:
                    Key.erase(K_DOWN);
                    break;

                case SDLK_z:
                    Hakurei.Shoot(false);
                    break;

                case SDLK_LSHIFT:
                    Hakurei.PressShift(false);
                    break;

                case SDLK_p:
                    if(current_display == PROCESS)
                    {
                        if(is_loser or is_winner) return;
                        is_paused = !is_paused;
                        if(is_paused)
                        {
                            Hakurei.pause();
                            for(auto &x : enemy) x.pause();
                            for(auto &x : shot) x.pause();
                        }
                        else
                        {
                            Hakurei.resume();
                            for(auto &x : enemy) x.resume();
                            for(auto &x : shot) x.resume();
                        }
                    }
                    break;
                case SDLK_RETURN:
                    if(current_display == PROCESS)
                    {
                        if(is_paused and !is_loser and !is_winner)
                        {
                            is_paused = false;
                            Hakurei.resume();
                            for(auto &x : enemy) x.resume();
                            for(auto &x : shot) x.resume();
                        }
                        if(is_loser)
                        {
                            reset();
                        }
                        if(is_winner)
                        {
                            Mix_HaltMusic();

                            is_noti = false;
                        
                            ofstream file("res/dat/notification.txt");
                            file << "false";

                            file.close();

                        //    Mix_HaltChannel(-1);

                            scene = END;
                        }
                    }
                    break;

                default:
                    break;
            }
            if (Key.empty())
            {
                Hakurei.SetMove(false);
                Hakurei.SetStatus(Hakurei.IDLE);
            }
            else
            {
                Hakurei.SetStatus(*Key.begin() + 1);
                Hakurei.Move();
            }
        }
    }
}

void Stage::reset()
{
    stage_time.Reset();

    enemy.clear();
    shot.clear();

    if(is_loser) Hakurei.setRessurect(true);

    is_loser = false;
    is_winner = false;
    
    createEnemy();
    
    life = default_life;
    explode = default_explode;
    score = 0;


    stage_content_alpha = 255;
    stage_content_blur = false;
    stage_name.setPos(250, SCREEN_HEIGHT / 2 - 100);
    stage_content.setPos(620, 720);
    current_display = INTRO;


    story.reset();
    game_end.reset();
}