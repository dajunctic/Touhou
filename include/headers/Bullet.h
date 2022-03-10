#if !defined(BULLET_H_)
#define BULLET_H_
#include "GameObject.h"

class Bullet{
public:
    enum TypeName{
        VECTOR,
        HORIZONTAL_SIN,
        VERTICAL_SIN
    };

    Bullet();
    ~Bullet();

    void SetName(const int& name_){name = name_;};
    void SetType(const int& type_){ type = type_;};
    void SetStartPoint(const double& start_){ start_point = start_;};
    void SetPos(const double& x_, const double& y_) { x = x_; y = y_; };
    pair<double, double> GetPos() const { return {x , y}; };

    void SetSpeed (const double& x_speed_, const double& y_speed_){ x_speed = x_speed_; y_speed = y_speed_;};
    void SetAngle(const double& angle_){ angle = angle_;};

    
    void SetRandomAngle(const int& st, const int& en);

    void HandleMove();

private:
    int type;
    int name;

    double x, y;
    
    double x_speed, y_speed;

    double angle; // degree
    double start_point;

};

#endif // BULLET_H_
