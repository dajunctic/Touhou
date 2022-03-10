#if !defined(ENEMY_H_)
#define ENEMY_H_

#include "GameObject.h"

class Enemy{
public:
    Enemy();
    ~Enemy();

private:
    int name;
    int type;

    double x, y;

    
};


#endif // ENEMY_H_
