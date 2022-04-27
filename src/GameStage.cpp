#include "GameStage.h"

void Stage::Load(SDL_Renderer * renderer)
{
    level_theme.Load(renderer, "res/gui/theme_difficulty.png");
    level_img.Load(renderer, "res/gui/difficulty.png");
    select.Load(renderer, "res/gui/select_.png");

    esc.Load(renderer, "res/gui/esc.png");
    esc.SetRect((SCREEN_WIDTH - esc.GetRect().w)/2, SCREEN_HEIGHT - esc.GetRect().h);


    // Story //
    story.load(renderer);
    // End // 
    game_end.load(renderer);

     /* Load Game Image */{   
        GameBg.Load(renderer, "res/img/bg/theme_03.jpg");
        GameBg.SetRect(170, 0);
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


        for(int i = 0 ; i < 6 ; i++)
        {
            string path = "res/img/char/power_0" + to_string(i) + ".png";
            powershard_img[i].Load(renderer, path);
        }
    }
    /* Load Character */
    {
        Hakurei.Set(8 , 10);
        Hakurei.SetPos(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT - 200);
        Hakurei.Load(renderer, "hakurei");
    }
    /* Load Enemy */
    {
        explosion_img.Load(renderer, "res/gui/animation/explosion.png");

        for(int i = 0 ; i < 2 ; i++)
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
    /* Charpter 1 */
    {
    //    Enemy Test2;
    
        int truth = 1;

        for(int i = 700 ; i <= 900 ; i += 200)
        {
            truth -= 1;
            Enemy Test;

            Test.SetPos(i , 200);
            Test.Set(4, 10, 2);
            Test.SetName(1);
            Test.Load(enemy_img[1]);
            Test.SetFitAttackFrame(11.0, 0.0);
            Test.InitBullet(0 , 2, 0, 11);  

            /*
            Test.SetOrbit(2,0,{2,2},-0.01, 90);

            Test.SetOrbit(5, 0,{2,2}, 0, -90);
            Test.SetOrbit(7, 0,{0,0}, 0, 90);

            // Hinh elip //
            int tmp = 8, tmp2 = 0;
            for(int j = -90 ; j < 270 ; j+=5)
            {
                Test.SetOrbit(tmp, tmp2, {2.5,1}, 0,  j + 180 * truth);
                tmp2 += 5;
                if(tmp2 >= 60){
                    tmp++;
                    tmp2 = 0;
                }
            }
            Test.SetOrbit(tmp, tmp2, {0,0}, 0, 180);
            */

            enemy.push_back(Test);
        }

        // Real //

        /* BOSS */
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
        }
    }
}

void Stage::Show(SDL_Renderer * renderer)
{
    if(scene == LEVEL_CHOICE){
        level_theme.Render(renderer);
        select.SetRect((SCREEN_WIDTH - select.GetRect().w)/2, 216 + level * 75);
        select.Render(renderer);

        level_img.Render(renderer);
        
        esc.Render(renderer);
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
        GameBg.Render(renderer);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0 , 100);
        // SDL_RenderFillRect(renderer, &MainBoard);
        bomb.show(renderer);

        Hakurei.Show(renderer);
        Hakurei.HandleBullet(enemy);

        /* Display Enemy */
    
        HandleEnemy(renderer);
        HandleShot(renderer);

        /* Show Another */
        StageBg.Render(renderer);
        life_text.show(renderer);
        explode_text.show(renderer);
        score_text.show(renderer);
        hakurei_animation.show(renderer);
    }
}

void Stage::HandleEnemy(SDL_Renderer * renderer)
{   

    for(auto &x : enemy)
    {
        if(bomb.isAttack())
        {
            x.minusHealhPoint(bomb_power);
        }
    }
    
    // Take Score
    for(auto &x : shards)
    {
        if(RectInRect(x.getRect(), Hakurei.getRect()))
        {
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

        erased_enemy.push_back(x);
    } 
    enemy = erased_enemy;

    // show enemy
    for(auto &x : enemy)
    {
        if(x.IsBoss())
        {
            x.Show(renderer, boss_img[x.GetName()][x.GetStatus()]);
        }
        else
        { 
            x.Show(renderer, enemy_img[x.GetName()][x.GetStatus()]);
        }
        x.HandleMove();
        x.HandleBullet(shot);

    }

    // show powershard
    vector<PowerShard> erased_shards;
    for(auto &x : shards)
    {
        if(x.isDelete()) continue;
        erased_shards.push_back(x);
    }
    shards = erased_shards;

    for(auto &x : shards)
    {
        x.show(renderer, &powershard_img[x.getType()], Hakurei.GetCenter());
    }

    // show explosion
    vector<Animation> erased_explosion;
    for(auto &x : explosion)
    {
        if(x.isDelete()) continue;
        erased_explosion.push_back(x);
    }
    explosion = erased_explosion;

    for(auto &x : explosion)
    {
        x.show(renderer, &explosion_img);
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

        if(s->IsDelete())
        {
            Hakurei.Die(true);
            life --;
            life_text.setText(renderer, to_string(life));
            if(life)
            {
                Hakurei.setRessurect(true);
            }

        }

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