#if !defined(GAME_PHYSICS_H_)
#define GAME_PHYSICS_H_

#include "Touhou.h"

double distance(pair<double, double> , pair<double,double> );
double vector_length(pair<double, double> );
double cos(pair<double,double>, pair<double, double>);
double sin(pair<double,double>, pair<double, double>);

bool PointInCircle(pair<double,double> P, pair<double, double> O, double r);
bool RectInRect(SDL_Rect a, SDL_Rect b);
bool PointInRect(SDL_Rect rect, double rotation, double pointX, double pointY);
bool SegmentInCircle(double circleCenterX, double circleCenterY, double circleRadius, double lineAX, double lineAY, double lineBX, double lineBY);
bool RectInCircle(SDL_Rect rect, double rotation, pair<double, double> I, double r); // 

#endif // GAME_PHYSICS_H_
