#if !defined(ENEMY_H_)
#define ENEMY_H_

#include "GameObject.h"
#include "Bullet.h"
#include "ImpTimer.h"

struct Plan{
    int start_time, end_time; // time
    int type;
    Plan(int start_time, int end_time, int type = 0){
        this->start_time = start_time;
        this->end_time = end_time;
        this->type = type;
    }
};

class Enemy{
public:
    // 0:    ENEMY_IDLE,
    // 1:    ENEMY_LEFT,
    // 2:    ENEMY_RIGHT

    Enemy();
    ~Enemy();

    void SetName(const int& name_){name = name_;};
    void SetType(const int& type_){ type = type_;};
    void SetPos(const double& x_, const double& y_) { x = x_; y = y_; };
    pair<double, double> GetPos() const { return {x , y}; };
     pair<double, double> GetCenterPos() const { return {center_x, center_y}; };

    void SetSpeed (const double& x_speed_, const double& y_speed_){ x_speed = x_speed_; y_speed = y_speed_;};
    void SetAngle(const double& angle_){ angle = angle_;};

    
    void SetRandomAngle(const int& st, const int& en);

    void HandleMove();

    void InitBullet(int start_time, int end_time, int type);
    void HandleBullet(vector<Bullet> & shot);
    void MakeBullet(vector<Bullet> & shot, int type);

    void Set(int number_frames_, int time_per_frame_){
        number_frames = number_frames_;
        time_per_frame = time_per_frame_;
    }
    void Load(SDL_Renderer * screen, string id){

        string path = "res/img/enemy/enemy_";
        img[0].LoadImage(screen, path + id + ".png");
        img[1].LoadImage(screen, path + id + "_left.png");
        img[2].LoadImage(screen, path + id + "_right.png");

        int imageWidth = img[0].GetRect().w;
        int imageHeight = img[0].GetRect().h;
        int frameWidth = imageWidth / number_frames;

        for(int i = 0 ; i < 3 ; i++){
            for(int k = 0 ; k < number_frames ; k++){
                frame_clip[i][k].x = k * frameWidth;
                frame_clip[i][k].y = 0;
                frame_clip[i][k].w = frameWidth;
                frame_clip[i][k].h = imageHeight;
            }
        }
    }
    void Update(){
        center_x = (x + img[current_status].GetRect().w / number_frames + x) / 2;
        center_y = (y + img[current_status].GetRect().h + y) / 2;

        EnemyTime.Update();
        time_count++;
        if(time_count % time_per_frame == 0){
            current_frame ++;
            current_frame %= number_frames;
        }
    }
    void Show(SDL_Renderer * screen){
        Update();

        SDL_Texture* p_object = img[current_status].GetObject();
        SDL_Rect rect = img[current_status].GetRect();

        SDL_Rect renderquad = { int(x) , int(y) , rect.w / number_frames, rect.h };
        SDL_RenderCopy(screen, p_object, &frame_clip[current_status][current_frame], &renderquad);
    }

private:
    int type;
    int name;

    double x, y;
    double center_x, center_y;
    
    double x_speed, y_speed;

    double angle; // degree

    /* Enemy Display */
    Object img[4];

    int current_status; 
    int current_frame;
    int number_frames;
    int time_count;
    int time_per_frame;
    SDL_Rect frame_clip[4][20];


    GameTime EnemyTime;
    /* Enemy move */
    bool is_move;

    vector<Plan> plan;
};



#endif // ENEMY_H_
