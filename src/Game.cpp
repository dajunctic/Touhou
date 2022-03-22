#include "Game.h"


void Game::load(){
    
    /* Load Game Object */{   
        GameBg.LoadImage(screen, "res/img/background.jpg");
        GameBg2.LoadImage(screen, "res/img/bg.png");

        for(int i = 0 ; i < 9 ; i++){
            string id = to_string(i);
            if(i < 10) id = '0' + id;
            string path = "res/img/bullet/b_" +  id + ".png";
            shot_img[i].LoadImage(screen, path);
        }
    }
    /* Load Character */{
        Hakurei.Set(8 , 5);
        Hakurei.SetPos(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT - 200);
        Hakurei.Load(screen, "hakurei");
    }
    /* Load Enemy */{

        for(int i = 0 ; i < 2 ; i++){
            string path = "res/img/enemy/enemy_";
            string tmp = to_string(i);
            if(i < 10) tmp = '0' + tmp;

            enemy_img[i][0].LoadImage(screen, path + tmp + ".png");
            enemy_img[i][1].LoadImage(screen, path + tmp + "_left.png");
            enemy_img[i][2].LoadImage(screen, path + tmp + "_right.png");
        //    enemy_img[i][3].LoadImage(screen, path + tmp + "_attack.png");
        }

    // Stage 1
    {
        Enemy Test;
    //    Enemy Test2;

        for(int i = 500 ; i <= 700 ; i += 200){

            Test.SetPos(i , 200);
            Test.Set(4, 10);
            Test.SetName(1);
            Test.Load( enemy_img[1][0].GetRect());
            Test.InitBullet(0 , 10, 0);  

            Test.SetOrbit(2,2, 60,{2,2},-0.01, 90);

            Test.SetOrbit(5,5, 60,{2,2}, 0, -90);
            Test.SetOrbit(7,7, 60,{0,0}, 0, 90);

            enemy.push_back(Test);
        }
    }
 
    }
}

void Game::display(){
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
            shot_img[x.GetName()].Render(screen);
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

void Game::HandleEnemy(){

    for(auto &x : enemy){
        x.Show(screen, enemy_img[x.GetName()][x.GetStatus()]);
        x.HandleMove();
        x.HandleBullet(shot);
    }
}


void Game::HandleInput(SDL_Event e){
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