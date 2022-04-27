#ifndef POWER_SHARD_H
#define POWER_SHARD_H

#include "Touhou.h"
#include "GameImage.h"
#include "GamePhysics.h"

class PowerShard
{
    private:
        int type; // type  
        double x, y; // coordinate

        double v; // velocity
        double a; // acceleration

        SDL_Rect rect; // size

        bool is_delete;

        double angle; // angle 
        double speed;

    public:
        PowerShard();

        void set(int, double, double);
        int getType();
        SDL_Rect getRect();
        void setDelete();
        bool isDelete();
        void load(Image *);
        void show(SDL_Renderer *, Image *, pair<double,double>);


};

#endif // !POWER_SHARD_H