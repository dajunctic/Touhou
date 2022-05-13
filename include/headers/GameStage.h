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
    Mix_Music * bgm = NULL;
    bool isBgm = true;

    multiset<int> Key;
    Image level_theme;
    Image level_img; /* Level of difficulty */
    Image select;
    int level = EASY;

    Image esc;
    int scene = MAIN;

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



    int explode = 3;
    int default_life = 3;
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
    Enemy boss = Enemy(true);

    /* Bullet */
    vector<Bullet> shot;
    Image shot_img[20];

    /* Explosion */
    vector<Animation> explosion;
    Image explosion_img;

    Bomb bomb;
    int bomb_power = 200;

    Image powershard_img[6];
    vector<PowerShard> shards;

    bool is_paused = false;
    Image pause;
    Image die;
    Image win;

    bool is_loser = false;
    bool is_winner = false;

    Mix_Chunk * dead_sfx = NULL;
    Mix_Chunk * enemy_dead = NULL;

public:
    Stage(){};
    ~Stage(){};

    void Load(SDL_Renderer * renderer);
    void Show(SDL_Renderer * renderer);

    void createEnemy();
    void HandleEnemy(SDL_Renderer * renderer);
    void HandleShot(SDL_Renderer * renderer);
    void HandleInput(SDL_Event e, int * SCENE);
};
#endif // GAME_STAGE_H_
