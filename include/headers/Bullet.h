#if !defined(BULLET_H_)
#define BULLET_H_

#include "GameImage.h"
#include "GamePhysics.h"
#include "GameTime.h"

class Bullet{
public:
    enum TypeName{
        VECTOR,
        HORIZONTAL_SIN,
        VERTICAL_SIN
    };
    vector<int> RadiusCollision {0, 1, 2 , 3, 4 , 5, 6, 7, 8, 9};

    Bullet();
    ~Bullet();

    void SetName(const int& name_){name = name_;};
    void SetType(const int& type_){ type = type_;};
    void SetStartPoint(const double& start_){ start_point = start_;};
    void SetPos(const double& x_, const double& y_) { x = x_; y = y_; };
    pair<double, double> GetPos() const { return {x , y}; };
    pair<double, double> GetCenterPos() const { return {center_x, center_y}; };

    int GetName() const { return name; };

    void SetSpeed (const double& x_speed_, const double& y_speed_){ x_speed = x_speed_; y_speed = y_speed_;};
    void SetAngle(const double& angle_){ angle = angle_;};
    double GetAngle() const { return angle; };
    
    void SetRandomAngle(const int& st, const int& en);

    void HandleMove();
    void HandleCollision(pair<double,double>, double, SDL_Rect ); // Handle Collision with the player //
    bool IsDelete() const{ return is_delete; };
    void setDelete();
private:
    int type;
    int name;

    double x, y;
    double center_x, center_y;
    
    double x_speed, y_speed;

    double angle; // degree
    double start_point;

    int status;

    bool is_delete;

};

/* Bomb */

class Bomb{
private:
    Image magic_cirle;
    double rotate_angle;
    double rotate_speed;

    Animation fire;
    Image amulet;

    Time bomb_time;

    Animation effect;

    bool is_used;
    bool is_attack;
public:
    Bomb();
    ~Bomb();

    void load(SDL_Renderer * renderer);
    void show(SDL_Renderer * renderer);
    void use();
    bool isUsed();
    bool isAttack();
    void setAttack(bool choice);
    void reset();
};

#endif // BULLET_H_
