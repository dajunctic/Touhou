#if !defined(GAME_STAGE_H_)
#define GAME_STAGE_H_

#include "Touhou.h"
#include "GameText.h"
#include "Character.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameStory.h"
#include "GameEnd.h"
#include "PowerShard.h"
#include "GameTime.h"
#include "GamePhysics.h"

enum DIFFICULTY{
    EASY,
    NORMAL,
    HARD,
    LEGENDARY,
    TOTAL_DIFFICULTY
};

enum SCENE{
    LEVEL_CHOICE,
    STORY,
    MAIN,
    END
};

enum MAIN_SCENE{
    INTRO,
    PROCESS,
    WIN,
    LOSE
};

class Stage{
private:
    Time stage_time;

    Mix_Music * bgm = NULL;
    bool isBgm = false;

    multiset<int> Key;

    // Level Choice //
    Image level_theme;
    Image level_img; /* Level of difficulty */
    Image default_level_img;
    Image select;
    int default_level = LEGENDARY;
    int level = EASY;
    bool is_default_level = false;

    Text esc;
    int scene = LEVEL_CHOICE;

    // Story //
    Story story;

    // End //
    End game_end;


    // Play //
    Image GameBg;
    Image StageBg;
    SDL_Rect MainBoard = {BOARD_X, BOARD_Y, BOARD_LIMITED_X - BOARD_X , BOARD_LIMITED_Y - BOARD_Y };
    
    // Game Play Display Process //
    int current_display = INTRO;
    Text stage_name;
    Text stage_content;
    int stage_content_alpha = 255;
    bool stage_content_blur = false;



    int default_explode = 5;
    int explode = default_explode;
    int default_life = 5;
    int life = default_life;
    Text explode_text;
    Text life_text;
    int score = 0;
    Text score_text;

    Animation hakurei_animation;

    Character Hakurei;

    /* Enemy */
    vector<Enemy> enemy;
    Image enemy_img[20][10];
    int wave_enemy = 0;

    /* Boss */
    Image boss_img[20][10];
    bool is_subboss = true;

    /* Bullet */
    vector<Bullet> shot;
    Image shot_img[40];

    /* Explosion */
    vector<Animation> explosion;
    Image explosion_img;

    Bomb bomb;
    int bomb_power = 200;
    Mix_Chunk * bomb_sfx;

    Image powershard_img[6];
    vector<PowerShard> shards;


    /* Game Status */
    bool is_paused = false;
    Image pause;
    Image die;
    Image win;

    bool is_loser = false;
    bool is_winner = false;

    Mix_Chunk * dead_sfx = NULL;
    Mix_Chunk * enemy_dead = NULL;

    /* Notification */
    Image noti_img;
    Text noti_text;
    double noti_x = 610;
    double noti_y = -65;
    double limit_noti_x = 1280;
    double limit_noti_y = 25;
    Time noti_time;

    bool is_noti = true;
    Mix_Chunk * noti = NULL;

public:
    Stage(){};
    ~Stage(){};

    void Load(SDL_Renderer * renderer);
    void Show(SDL_Renderer * renderer);

    void setNotification(bool);
    void setScene(int);
    void createEnemy();
    void createEnemyViaTime();
    void HandleEnemy(SDL_Renderer * renderer);
    void HandleCharacter(SDL_Renderer * renderer);
    void HandleShot(SDL_Renderer * renderer);
    void HandleInput(SDL_Event e, int * SCENE);
    void reset();
};
#endif // GAME_STAGE_H_
