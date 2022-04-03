#include "Game.h"


void Game::load(){
    /* Load Title Introduction */{
        dazu.Load(screen, "res/img/Dazu.png");
        dazu_warning.Load(screen, "res/img/warning.png");
        dazu.SetAlpha(dazu_alpha);
        dazu_sound = Mix_LoadWAV("res/sfx/DazuDazuGamer.wav");
        dazu_bg = Mix_LoadWAV("res/sfx/horror.wav");
    }
    /* Load Menu */{
        for(int i = 0 ; i < 4 ; i++){
            string path = "res/img/bg/menu_bg_0" + to_string(i) + ".jpg";
            menu_bg[i].Load(screen, path);
        }
        menu_bgm = Mix_LoadMUS("res/bgm/YourReality.mp3");
        tv = Mix_LoadWAV("res/sfx/tv.wav");
        menu.Load(screen);
    //    Mix_VolumeMusic(64);
    }
    
    /* Load Game Image */{   
        GameBg.Load(screen, "res/img/background.jpg");
        GameBg2.Load(screen, "res/img/bg.png");

        // Load bullet Image
        for(int i = 0 ; i < 12 ; i++){
            string id = to_string(i);
            if(i < 10) id = '0' + id;
            string path = "res/img/bullet/b_" +  id + ".png";
            shot_img[i].Load(screen, path);
        }
    }
    /* Load Character */{
        Hakurei.Set(8 , 10);
        Hakurei.SetPos(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT - 200);
        Hakurei.Load(screen, "hakurei");
    }
    /* Load Enemy */{
        for(int i = 0 ; i < 2 ; i++){
            string path = "res/img/enemy/enemy_";
            string tmp = to_string(i);
            if(i < 10) tmp = '0' + tmp;

            enemy_img[i][0].Load(screen, path + tmp + ".png");
            enemy_img[i][1].Load(screen, path + tmp + "_left.png");
            enemy_img[i][2].Load(screen, path + tmp + "_right.png");
            enemy_img[i][3].Load(screen, path + tmp + "_attack_left.png");
            enemy_img[i][4].Load(screen, path + tmp + "_attack_right.png");
        }
    }
    /* Load Boss */{
        for(int i = 1 ; i < 2 ; i++){
            string path = "res/img/boss/boss_";
            string tmp = to_string(i);
            if(i < 10) tmp = '0' + tmp;

            boss_img[i][0].Load(screen, path + tmp + "_idle.png");
            boss_img[i][1].Load(screen, path + tmp + "_left.png");
            boss_img[i][2].Load(screen, path + tmp + "_right.png");
            boss_img[i][3].Load(screen, path + tmp + "_attack_left.png");
            boss_img[i][4].Load(screen, path + tmp + "_attack_right.png");
        }

    }
    /* Charpter 1 */{
        Enemy Test;
    //    Enemy Test2;
    
        int truth = 1;

        for(int i = 500 ; i <= 700 ; i += 200){
            truth -= 1;

            Test.SetPos(i , 200);
            Test.Set(4, 10, 2);
            Test.SetName(1);
            Test.Load(enemy_img[1]);
            Test.SetFitAttackFrame(11.0, 0.0);
            Test.InitBullet(0 , 8, 2, 10);  

            Test.SetOrbit(2,0,{2,2},-0.01, 90);

            Test.SetOrbit(5, 0,{2,2}, 0, -90);
            Test.SetOrbit(7, 0,{0,0}, 0, 90);


            // Hinh elip //
            int tmp = 8, tmp2 = 0;
            for(int j = -90 ; j < 270 ; j+=5){
                Test.SetOrbit(tmp, tmp2, {2.5,1}, 0,  j + 180 * truth);
                tmp2 += 5;
                if(tmp2 >= 60){
                    tmp++;
                    tmp2 = 0;
                }
            }
            Test.SetOrbit(tmp, tmp2, {0,0}, 0, 180);

            enemy.push_back(Test);
        }



        // Real //

        /* BOSS */{
            boss.SetPos(640 - 20 , 200);
            boss.Set(4, 8, 7);
            boss.SetName(1);
            boss.Load(boss_img[1]);
            boss.SetFitAttackFrame(0.0, 25.0);
            boss.InitBullet(0 , 8, 2, 10);   

            boss.SetOrbit(2,0,{2,2},-0.01, 90);

            boss.SetOrbit(5, 0,{2,2}, 0, -90);
            boss.SetOrbit(7, 0,{0,0}, 0, 90);

            // Hinh elip //
            int tmp = 8, tmp2 = 0;
            for(int j = -90 ; j < 270 ; j+=5){
                boss.SetOrbit(tmp, tmp2, {2.5,1}, 0,  j );
                tmp2 += 5;
                if(tmp2 >= 60){
                    tmp++;
                    tmp2 = 0;
                }
            }
            boss.SetOrbit(tmp, tmp2, {0,0}, 0, 180);

            // boss.SetOrbit(1,0,{4,4},-0.01, 90);

            // boss.SetOrbit(4, 0,{2,2}, 0, -45);
            // boss.SetOrbit(6, 0,{0,0}, 0, 180);
            // boss.SetOrbit(7, 0,{4,4}, 0, 180);
            // boss.SetOrbit(8, 0,{0,0}, 0, 180);

            enemy.push_back(boss);
        }
    }
}

void Game::display(){
    if(SCENE == TITLE){
        if(g_time.CheckTime(2 , 0))
            Mix_PlayChannel(-1, dazu_sound , 0); 

        if(g_time.CheckTime(0 , 1))
            Mix_PlayChannel(-1, dazu_bg , 0); 
        
        if(g_time.CheckPeriod(0, 4) or g_time.CheckPeriod(10, 17)){
            if(dazu_alpha + 1 > 255) dazu_alpha = 255;
            else dazu_alpha += 1;
        }
        else{
            if(dazu_alpha - 1 < 0) dazu_alpha = 0;
            else dazu_alpha -= 1;
        }
        
        if(g_time.CheckPeriod(0, 10)){
            dazu.SetAlpha(dazu_alpha);
            dazu.Render(screen);
        }

        if(g_time.CheckPeriod(10, 25)){
            dazu_warning.SetAlpha(dazu_alpha);
            dazu_warning.Render(screen);
        }
        if(g_time.CheckTime(22))
            Mix_PlayChannel(-1, tv, 0);
        if(g_time.CheckTime(25)){
            Mix_HaltChannel(-1);
            g_time.Reset();
            SCENE = MENU;
        }
    }
    if(SCENE == MENU){
        if(g_time.CheckTime(0 , 1)){
            Mix_PlayMusic(menu_bgm, -1);
        }

        if(g_time.GetSeconds() % 4 == 0 and g_time.GetFrameTime() == 0){
            current_menu_bg ++;
            current_menu_bg %= 4;
        }
        menu_bg[current_menu_bg].Render(screen);
        menu.show(screen);
    }

    if(SCENE == PLAY){
        GameBg.Render(screen);
        SDL_SetRenderDrawColor(screen, 0, 0, 0 , 100);
        SDL_RenderFillRect(screen, &MainBoard);

        Hakurei.Show(screen);
        Hakurei.HandleBullet(enemy);

        /* Display Enemy */
        HandleEnemy();

        /* Display Bullet and Shot */{
            for(auto &x : shot){
                x.HandleMove();
                int w = shot_img[x.GetName()].GetRect().w;
                int h = shot_img[x.GetName()].GetRect().h;

                shot_img[x.GetName()].SetRect(x.GetPos().fi - w / 2, x.GetPos().se - h / 2);
                shot_img[x.GetName()].RenderAngle(screen, 90 + x.GetAngle());
            }
            vector<Bullet> tmp;

            for(auto &s : shot){
                int w = shot_img[s.GetName()].GetRect().w;
                int h = shot_img[s.GetName()].GetRect().h;
                int x = s.GetPos().fi;
                int y = s.GetPos().se;

                if (x + w <= BOARD_X or y + h <= BOARD_Y or x >= BOARD_LIMITED_X or y >= BOARD_LIMITED_Y){
                    continue;
                }else
                    tmp.push_back(s);
            
            shot = tmp;
                
            }
        }

        GameBg2.Render(screen);
    }

}

void Game::HandleEnemy(){

    for(auto &x : enemy){
        if(x.IsBoss())
            x.Show(screen, boss_img[x.GetName()][x.GetStatus()]);
        else 
            x.Show(screen, enemy_img[x.GetName()][x.GetStatus()]);
        x.HandleMove();
        x.HandleBullet(shot);

    }
}


void Game::HandleInput(SDL_Event e){
    if(SCENE == PLAY){
        if(e.type == SDL_KEYDOWN){

            switch (e.key.keysym.sym){
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

            case SDLK_LSHIFT:
                Hakurei.PressShift(true);
                break;
            
            default:
                break;
            }
            
        } 
        if(e.type == SDL_KEYUP){
            switch (e.key.keysym.sym){
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

            default:
                break;
            }
            if (Key.empty()){
                Hakurei.SetMove(false);
                Hakurei.SetStatus(Hakurei.IDLE);
            }
            else{
                Hakurei.SetStatus(*Key.begin() + 1);
                Hakurei.Move();
            }
        }
    }
    if(SCENE == MENU){
        menu.HandleInput(e, &quit, window);
    }
}