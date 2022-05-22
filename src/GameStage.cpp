#include "GameStage.h"

void Stage::Load(SDL_Renderer * renderer)
{
    stage_time.Start();

    // Level Choice //
    level_theme.Load(renderer, "res/gui/theme_difficulty.png");
    default_level_img.Load(renderer, "res/gui/default_level.png");
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
        for(int i = 0 ; i < 30 ; i++){
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

        for(int i = 0 ; i < 8 ; i++)
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
    bgm = Mix_LoadMUS("res/bgm/AwakeningoftheEarthSpirits.mp3");

    dead_sfx = Mix_LoadWAV("res/sfx/dead.wav");
    enemy_dead = Mix_LoadWAV("res/sfx/enemy_dead.wav");
}

void Stage::createEnemy()
{
    enemy.clear();
    shot.clear();

    int wave_time = 0;
    int secwave_time = 10;
    int thiwave_time = 20;
    int fouwave_time = 20;
    int fifwave_time = 5;
    int sixwave_time = 5;
    int subboss_time = 60;

    Enemy FstWaveR[6],  FstWaveL[6];
    Enemy SecondWaveR[6],  SecondWaveL[6];
    Enemy ThirdWaveR[8], ThirdWaveL[8];
    Enemy FourthWave[10];
    Enemy FifthWave[12];
    Enemy SixthWave[12];
    Enemy SubBoss, boss;

/* ################            1ST ENEMY WAVE           ####################*/

FSTWAVE:
    //goto SUBBOSSWAVE;
    // goto BOSSWAVE;

    
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

        FstWaveR[i].setDeleteTime(8 + i, 30);
        FstWaveL[i].setDeleteTime(8 + i, 30);
    }

    for (int i = 1; i < 6; i++) {
        FstWaveR[i].InitBullet(2+i,3+i,19-i,11);
        FstWaveL[i].InitBullet(2+i,3+i,8+i,11);

        FstWaveR[i].InitBullet(1 + i,3 + i,4,20);
        FstWaveL[i].InitBullet(1 + i,3 + i,4,20);
    }
    for (int i = 0; i < 6; i++) {
        FstWaveR[i].setHeathPoint(10);
        FstWaveL[i].setHeathPoint(10);

        enemy.push_back(FstWaveR[i]);
        enemy.push_back(FstWaveL[i]);
    }
    wave_time = 10;

/* ################            2ND ENEMY WAVE           ####################*/
SECWAVE:
    // goto THIWAVE;
    for (int i = 0; i < 6; i++) 
    {
        int nameR = 2 + int(rand() % (1 - 0 + 1));
        int nameL = 2 + int(rand() % (1 - 0 + 1));

        SecondWaveR[i].SetPos(1321, 160);
        SecondWaveR[i].Set(4, 10);
        SecondWaveR[i].SetName(nameR);
        SecondWaveR[i].Load(enemy_img[nameR]);

        SecondWaveL[i].SetPos(270, 80);
        SecondWaveL[i].Set(4, 10);
        SecondWaveL[i].SetName(nameL);
        SecondWaveL[i].Load(enemy_img[nameL]);
    }    
    for (int i = 0; i < 6; i++) 
    {
        SecondWaveR[i].SetOrbit(wave_time + i,0,{3,3},0,180);
        SecondWaveL[i].SetOrbit(wave_time + i,0,{3,3},0,0);
  
        SecondWaveR[i].SetOrbit(wave_time + 6,10,{0,0},0,0);
        SecondWaveL[i].SetOrbit(wave_time + 6,10,{0,0},0,0);

        if(i % 2){
            SecondWaveR[i].SetOrbit(wave_time + 7,0,{3,3},-0.02,60);
            SecondWaveL[i].SetOrbit(wave_time + 7,0,{3,3},-0.02,120);
        }
        else{
            SecondWaveR[i].SetOrbit(wave_time + 7,0,{2,2},-0.02,120);
            SecondWaveL[i].SetOrbit(wave_time + 7,0,{2,2},-0.02,60);
        }

        for(int j = 1 ; j <= 30 ; j++){
            int randomAngleR = rand() % (360 - 0 + 1) + 0;
            int randomAngleL = rand() % (360 - 0 + 1) + 0;

            SecondWaveR[i].SetOrbit(wave_time + j + 7,0,{4,4},-0.04,randomAngleR);
            SecondWaveL[i].SetOrbit(wave_time + j + 7,0,{4,4},-0.04,randomAngleL);

            SecondWaveR[i].InitBullet(wave_time + j + 7,wave_time + j + 10,3,1);
            SecondWaveL[i].InitBullet(wave_time + j + 7,wave_time + j + 10,3,2);
        }

        SecondWaveR[i].setDeleteTime(wave_time + 7);
        SecondWaveL[i].setDeleteTime(wave_time + 7);
    }
    
    for (int i = 0; i < 6; i ++) 
    {
        SecondWaveR[i].InitBullet(wave_time + i,wave_time + 5+i,7,11);
        SecondWaveL[i].InitBullet(wave_time + i,wave_time + 5+i,7,12);

        SecondWaveR[i].InitBullet(wave_time + 1 + i,13,8,17);
    }

    
    //SecondWaveL[4].InitBullet(wave_time + 4,15,8,11);

    for (int i = 0; i < 6; i++) 
    {
        SecondWaveR[i].setHeathPoint(15);
        SecondWaveL[i].setHeathPoint(15);

        enemy.push_back(SecondWaveR[i]);
        enemy.push_back(SecondWaveL[i]);

        SecondWaveR[i].resetOrbit();
        SecondWaveL[i].resetOrbit();
    }

    wave_time += secwave_time;
    
/* ################            3RD ENEMY WAY           ####################*/
THIWAVE:
    // goto FOUWAVE;
    
    for (int i = 0; i < 8; i++) 
    {
        int posY = (i >= 4) ? 0 : -100;
        int nameR = 4 + int(rand() % (5 - 4 + 1));
        int nameL = 4 + int(rand() % (5 - 4 + 1));

        ThirdWaveR[i].SetPos(280, posY);
        ThirdWaveR[i].Set(4, 10);
        ThirdWaveR[i].SetName(nameR);
        ThirdWaveR[i].Load(enemy_img[nameR]);

        ThirdWaveL[i].SetPos(1280,posY);
        ThirdWaveL[i].Set(4, 10);
        ThirdWaveL[i].SetName(nameL);
        ThirdWaveL[i].Load(enemy_img[nameL]);
    }

    for (int i = 0; i < 4; i++) 
    {
        ThirdWaveR[i].SetOrbit(wave_time + 4 + i,0,{2,2},0,25);
        ThirdWaveR[i].InitBullet(wave_time + 5 + i,wave_time + 8 + i,5,11);

        ThirdWaveL[i].SetOrbit(wave_time + 4 + i,0,{2,2},0,155);
        ThirdWaveL[i].InitBullet(wave_time + 5 + i,wave_time + 8 + i,5,11);
    }
    for (int i = 4; i < 8; i++) 
    {
        ThirdWaveR[i].SetOrbit(wave_time + i,30,{2,2},0,25);
        ThirdWaveR[i].InitBullet(wave_time + 1 + i,wave_time+ 3 + i,5,11);

        ThirdWaveL[i].SetOrbit(wave_time + i,30,{2,2},0,155);
        ThirdWaveL[i].InitBullet(wave_time + 1 + i,wave_time+ 4 + i,5,11);
    }
    
    for(int i = 0 ; i < 8 ; i++){
        ThirdWaveR[i].SetOrbit(wave_time + 12,30,{0,0},0,0);
        ThirdWaveL[i].SetOrbit(wave_time + 12,30,{0,0},0,0);

        ThirdWaveL[i].InitBullet(wave_time + 10,wave_time+ 18,2,19);
        ThirdWaveR[i].InitBullet(wave_time + 10,wave_time+ 18,2,19);

        ThirdWaveR[i].SetOrbit(wave_time + 13,0,{2-(i%4)/3.3,2-(i%4)/3.3},-0.01,-90);
        ThirdWaveL[i].SetOrbit(wave_time + 13,0,{2-(i%4)/3.3,2-(i%4)/3.3},-0.01,-90);

        if(i >= 4){
            ThirdWaveR[i].SetOrbit(wave_time + 15,0,{2,2},-0.01,-90);
        //    ThirdWaveL[i].SetOrbit(wave_time + 15,0,{2,2},-0.01,90);
        }
        else{
        //    ThirdWaveR[i].SetOrbit(wave_time + 15,0,{2,2},-0.01,90);
            ThirdWaveL[i].SetOrbit(wave_time + 15,0,{2,2},-0.01,90);
        }

        ThirdWaveR[i].SetOrbit(wave_time + 17,0,{3,3},0,170);
        ThirdWaveL[i].SetOrbit(wave_time + 17,0,{3,3},0,10);

        ThirdWaveR[i].setDeleteTime(wave_time + 22);
        ThirdWaveL[i].setDeleteTime(wave_time + 22);
        
    }

    for (int i = 0; i < 8; i++) 
    {
        ThirdWaveR[i].setHeathPoint(20);
        ThirdWaveL[i].setHeathPoint(20);

        enemy.push_back(ThirdWaveR[i]);
        enemy.push_back(ThirdWaveL[i]);

        ThirdWaveR[i].resetOrbit();
        ThirdWaveL[i].resetOrbit();
    }
    wave_time += thiwave_time;

/* ################            4TH ENEMY WAY           ####################*/
FOUWAVE:
    // goto FIFWAVE;
    
    FourthWave[0].SetPos(360,-140);
    FourthWave[1].SetPos(450,-100);
    FourthWave[2].SetPos(540,-120);
    FourthWave[3].SetPos(630,-180);
    FourthWave[4].SetPos(720,-200); 
    FourthWave[5].SetPos(810,-220);
    FourthWave[6].SetPos(900,-170);
    FourthWave[7].SetPos(990,-140);
    FourthWave[8].SetPos(1080,-130);
    FourthWave[9].SetPos(1160,-210);
    for (int i = 0; i < 10; i++) {
        FourthWave[i].Set(4, 10);
        FourthWave[i].SetName(6);
        FourthWave[i].Load(enemy_img[6]);
        FourthWave[i].InitBullet(wave_time + 2,wave_time + 11 ,6,11);
    }

    // default = 23
    FourthWave[0].SetOrbit(wave_time,0,{3,3},-0.01,90);
    FourthWave[3].SetOrbit(wave_time,30,{3,3},-0.01,90);
    FourthWave[8].SetOrbit(wave_time + 1,0,{3,3},-0.01,90);
    FourthWave[5].SetOrbit(wave_time + 1,30,{3,3},-0.01,90);
    FourthWave[9].SetOrbit(wave_time + 2,0,{3,3},-0.01,90);
    FourthWave[1].SetOrbit(wave_time + 2,30,{3,3},-0.01,90);
    FourthWave[6].SetOrbit(wave_time + 3,0,{3,3},-0.01,90);
    FourthWave[7].SetOrbit(wave_time + 3,30,{3,3},-0.01,90);
    FourthWave[4].SetOrbit(wave_time + 4,0,{3,3},-0.01,90);
    FourthWave[2].SetOrbit(wave_time + 4,30,{3,3},-0.01,90);
    FourthWave[0].SetOrbit(wave_time + 14,0,{0,0},0.01,270);
    FourthWave[3].SetOrbit(wave_time + 14,30,{0,0},0.01,270);
    FourthWave[8].SetOrbit(wave_time + 15,0,{0,0},0.01,270);
    FourthWave[5].SetOrbit(wave_time + 15,30,{0,0},0.01,270);
    FourthWave[9].SetOrbit(wave_time + 16,0,{0,0},0.01,270);
    FourthWave[1].SetOrbit(wave_time + 16,30,{0,0},0.01,270);
    FourthWave[6].SetOrbit(wave_time + 17,0,{0,0},0.01,270);
    FourthWave[7].SetOrbit(wave_time + 17,30,{0,0},0.01,270);
    FourthWave[4].SetOrbit(wave_time + 18,0,{0,0},0.01,270);
    FourthWave[2].SetOrbit(wave_time + 19,30,{0,0},0.01,270);

    for(int i = 0 ; i < 10 ; i++){
        FourthWave[i].InitBullet(wave_time + 6,wave_time + 19 ,20 ,18);
    }

    for (int i = 0; i < 10; i++) {
        FourthWave[i].setHeathPoint(30);

        FourthWave[i].setDeleteTime(wave_time + 20);
        enemy.push_back(FourthWave[i]);
        FourthWave[i].resetOrbit();
    }

    wave_time += fouwave_time;

/* ################            5TH ENEMY WAY           ####################*/   
FIFWAVE:
    // goto SIXWAVE;

    for (int i = 0; i < 12; i++) {
        FifthWave[i].SetPos(340+ i*80, -60);
        FifthWave[i].Set(4, 10);
        FifthWave[i].SetName(3);
        FifthWave[i].Load(enemy_img[3]);
    }
    FifthWave[0].SetOrbit(wave_time + 0,0,{4,4},0,90);
    FifthWave[1].SetOrbit(wave_time + 0,15,{4,4},0,90);
    FifthWave[2].SetOrbit(wave_time + 0,30,{4,4},0,90);
    FifthWave[3].SetOrbit(wave_time + 0,45,{4,4},0,90);
    FifthWave[4].SetOrbit(wave_time + 1,0,{4,4},0,90);
    FifthWave[5].SetOrbit(wave_time + 1,15,{4,4},0,90);
    FifthWave[6].SetOrbit(wave_time + 1,30,{4,4},0,90);
    FifthWave[7].SetOrbit(wave_time + 1,45,{4,4},0,90);
    FifthWave[8].SetOrbit(wave_time + 2,0,{4,4},0,90);
    FifthWave[9].SetOrbit(wave_time + 2,15,{4,4},0,90);
    FifthWave[10].SetOrbit(wave_time + 2,30,{4,4},0,90);
    FifthWave[11].SetOrbit(wave_time + 2,45,{4,4},0,90);

    for(int i = 2 ; i <= 9 ; i++ ){
        int nameB = (i % 2) ? 11 : 15;

        FifthWave[i].InitBullet(wave_time + 1,wave_time + 3 ,21 ,nameB);
    }

    for (int i = 0; i < 12; i++) {
        FifthWave[i].setHeathPoint(10);

        FifthWave[i].setDeleteTime(wave_time + 10);
        enemy.push_back(FifthWave[i]);
        FifthWave[i].resetOrbit();
    }

    wave_time += fifwave_time;

SIXWAVE:
    // goto SUBBOSSWAVE;

    for (int i = 0; i < 12; i++) {
        SixthWave[i].SetPos(340+ (11-i)*80, -60);
        SixthWave[i].Set(4, 10);
        SixthWave[i].SetName(3);
        SixthWave[i].Load(enemy_img[3]);
    }
    SixthWave[0].SetOrbit(wave_time + 0,0,{4,4},0,90);
    SixthWave[1].SetOrbit(wave_time + 0,15,{4,4},0,90);
    SixthWave[2].SetOrbit(wave_time + 0,30,{4,4},0,90);
    SixthWave[3].SetOrbit(wave_time + 0,45,{4,4},0,90);
    SixthWave[4].SetOrbit(wave_time + 1,0,{4,4},0,90);
    SixthWave[5].SetOrbit(wave_time + 1,15,{4,4},0,90);
    SixthWave[6].SetOrbit(wave_time + 1,30,{4,4},0,90);
    SixthWave[7].SetOrbit(wave_time + 1,45,{4,4},0,90);
    SixthWave[8].SetOrbit(wave_time + 2,0,{4,4},0,90);
    SixthWave[9].SetOrbit(wave_time + 2,15,{4,4},0,90);
    SixthWave[10].SetOrbit(wave_time + 2,30,{4,4},0,90);
    SixthWave[11].SetOrbit(wave_time + 2,45,{4,4},0,90);

    for(int i = 2 ; i <= 9 ; i++ ){
        int nameB = (i % 2) ? 11 : 15;

        SixthWave[i].InitBullet(wave_time + 1,wave_time + 3 ,21 ,nameB);
    }

    for (int i = 0; i < 12; i++) {
        SixthWave[i].setHeathPoint(10);

        SixthWave[i].setDeleteTime(wave_time + 10);
        enemy.push_back(SixthWave[i]);
        SixthWave[i].resetOrbit();
    }

    wave_time += sixwave_time;

    if(is_subboss) goto SUBBOSSWAVE;
    else goto BOSSWAVE;

SUBBOSSWAVE: // turn boss phu

    SubBoss.setHeathPoint(9999999);
    SubBoss.SetPos((940 / 2 - 16) + 340 , -100);
    SubBoss.Set(5, 8);
    SubBoss.SetName(7);
    SubBoss.Load(enemy_img[7]);
    SubBoss.SetOrbit(wave_time + 1,0,{4,4},-0.04,90);

    for (int i = wave_time + 2; i < wave_time + 60; i += 20) {
        SubBoss.SetOrbit(2+i,0,{4,4},-0.05,320);
        SubBoss.SetOrbit(4+i,0,{4,4},-0.03,180);
        SubBoss.SetOrbit(6+i,0,{4,4},-0.05,40);

        SubBoss.InitBullet(1+i,1+i,2,26);
        SubBoss.InitBullet(2+i,4+i,22,19);
        SubBoss.InitBullet(3+i,4+i,23,0);
        SubBoss.InitBullet(3+i,3+i,2,26);
        SubBoss.InitBullet(4+i,6+i,22,19);
        SubBoss.InitBullet(5+i,6+i,23,0);
        SubBoss.InitBullet(5+i,5+i,2,26);


        SubBoss.SetOrbit(9+i,0,{5,5},0,90);
        SubBoss.SetOrbit(10+i,0,{1,1},0,270);
        SubBoss.SetOrbit(15+i,30,{0,0},0,0);
        SubBoss.InitBullet(6+i,10+i,22,13);
        
        SubBoss.InitBullet(10+i,20+i,1,7);
        SubBoss.InitBullet(10+i,20+i,25,6);
        SubBoss.InitBullet(11+i,19+i,24,23);
    }

    SubBoss.SetOrbit(wave_time + 60,0,{4,4},0,-90);
    SubBoss.setDeleteTime(wave_time + 65);
    enemy.push_back(SubBoss);

    wave_time += subboss_time;
    is_subboss = false;

    goto SECWAVE;

BOSSWAVE: 
    boss.SetPos((940 / 2 - 16) + 340 , -100);
    boss.Set(5, 8);
    boss.SetName(7);
    boss.Load(enemy_img[7]);
    boss.SetOrbit(wave_time + 1,0,{4,4},-0.03,90);
    for (int i = wave_time + 1; i <= 4000; i += 40) {
        boss.InitBullet(2+i,4+i,22,19);
        boss.InitBullet(3+i,4+i,23,0);
        boss.InitBullet(3+i,3+i,2,26);
        boss.InitBullet(4+i,6+i,22,19);
        boss.InitBullet(5+i,6+i,23,0);
        boss.InitBullet(5+i,5+i,2,26);

        boss.InitBullet(2+i,11+i,2,19);
        boss.InitBullet(3+i,3+i,25,3);
        boss.InitBullet(5+i,5+i,0,4);
        boss.InitBullet(7+i,7+i,25,9);
        boss.InitBullet(9+i,9+i,0,11);
        boss.InitBullet(11+i,11+i,25,17);

        boss.InitBullet(10+i,31+i,6,11);
        boss.InitBullet(10+i,31+i,20,18);
        boss.InitBullet(1+i,40+i,26,20);
        
        boss.InitBullet(20+i,22+i,4,9);
        boss.InitBullet(25+i,40+i,3,11);
        boss.InitBullet(25+i,40+i,20,2);
        boss.InitBullet(10+i,20+i,25,5);
        boss.InitBullet(10+i,20+i,1,6);

        
        boss.InitBullet(30+i,31+i,2,26);
        boss.InitBullet(32+i,34+i,22,19);
        boss.InitBullet(33+i,34+i,23,0);
        boss.InitBullet(33+i,33+i,2,26);
        boss.InitBullet(34+i,36+i,22,19);
        boss.InitBullet(35+i,36+i,23,0);
        boss.InitBullet(35+i,35+i,2,26);


        boss.SetOrbit(2+i,0,{3,3},-0.02, 0);
        boss.SetOrbit(5+i,0,{3,3},-0.01, 180);
        boss.SetOrbit(11+i,0,{3,3},-0.02, 0);
        boss.SetOrbit(15+i,0,{2,2},-0.01,72);
        //Ngoi sao
        boss.SetOrbit(20+i,0,{9,9},0,252);
        boss.SetOrbit(20+i,30,{9,9},0,108);
        boss.SetOrbit(21+i,0,{9,9},0,324);
        boss.SetOrbit(21+i,30,{9,9},0,180);
        boss.SetOrbit(22+i,0,{9,9},0,36);
        boss.SetOrbit(22+i,30,{2,2},-0.01,252);
        boss.SetOrbit(25+i,0,{3,3},-0.025,320);
        boss.SetOrbit(30+i,0,{3,3},-0.025,140);
        boss.SetOrbit(35+i,0,{3,3},-0.025,220);
        boss.SetOrbit(40+i,0,{3,3},-0.025,40);

    }
    boss.setHeathPoint(1000);
    enemy.push_back(boss);     
}

void Stage::createEnemyViaTime()
{
    return;
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

        if(is_default_level) default_level_img.Render(renderer);
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
        for(int i = 0 ; i < 7 - tmp ; i++) score_str = '0' + score_str;
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

    if(bomb.isAttack() or enemy.empty())
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

            int num = 4;
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
        if(x.isDelete()) continue;

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
        x.HandleBullet(shot, Hakurei.GetCenter(), default_level);

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
        Hakurei.reset();
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

    if(is_loser or is_winner or is_paused) return;
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

                default:
                    break;
            }
        }
        if(e.type == SDL_KEYUP){
            switch (e.key.keysym.sym)
            {

                case SDLK_ESCAPE:
                    *SCENE = 1; // MENU
                    break;
                
                case SDLK_RETURN:
                    if(!is_default_level){
                        is_default_level = true;
                        return;
                    }
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
    is_default_level = false;
    isBgm = false;

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