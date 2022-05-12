#include "GamePhysics.h"


double distance(pair<double, double> a, pair<double,double> b)
{
    return sqrt((a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se));
}

double vector_length(pair<double, double> a)
{
    return sqrt(a.fi * a.fi + a.se * a.se);
}

double cos(pair<double,double> a, pair<double, double> b)
{
    double numerator = a.fi * b.fi + a.se * b.se;
    double denominator = vector_length(a) * vector_length(b);
    return numerator / denominator;
}

double sin(pair<double,double> a, pair<double, double> b)
{
    double numerator = a.fi * b.fi + a.se * b.se;
    numerator = (numerator < 0) ? -numerator : numerator;

    double denominator = vector_length(a) * vector_length(b);
    return numerator / denominator;
}

bool PointInCircle(pair<double,double> P, pair<double, double> O, double r)
{
    double d = distance(P, O);
    return d <= r;
}

bool RectInRect(SDL_Rect a, SDL_Rect b)
{
    return a.x < b.x + b.w and a.x + a.w > b.x and a.y < b.y + b.h and a.h + a.y > b.y;
}

bool PointInRect(SDL_Rect rect, double rotation, double pointX, double pointY)
{
    double centerX = rect.x + rect.w / 2;
    double centerY = rect.y + rect.h / 2;

    if(rotation == 0)   // Higher Efficiency for Rectangles with 0 rotation.
        return abs(centerX -pointX) < rect.w / 2 and abs(centerY-pointY) < rect.h / 2;

    double tx = cos(rotation)*pointX - sin(rotation)*pointY;
    double ty = cos(rotation)*pointY + sin(rotation)*pointX;

    double cx = cos(rotation)*centerX - sin(rotation)*centerY;
    double cy = cos(rotation)*centerY + sin(rotation)*centerX;

    return abs(cx-tx) < rect.w / 2 and abs(cy-ty) < rect.h / 2;
}

bool SegmentInCircle(double circleCenterX, double circleCenterY, double circleRadius, double lineAX, double lineAY, double lineBX, double lineBY)
{
    double lineSize = sqrt(pow(lineAX-lineBX, 2) + pow(lineAY-lineBY, 2));
    double distance;

    if (lineSize == 0) {
        distance = sqrt(pow(circleCenterX-lineAX, 2) + pow(circleCenterY-lineAY, 2));
        return distance < circleRadius;
    }

    double u = ((circleCenterX - lineAX) * (lineBX - lineAX) + (circleCenterY - lineAY) * (lineBY - lineAY)) / (lineSize * lineSize);

    if (u < 0) {
        distance = sqrt(pow(circleCenterX-lineAX, 2) + pow(circleCenterY-lineAY, 2));
    } else if (u > 1) {
        distance = sqrt(pow(circleCenterX-lineBX, 2) + pow(circleCenterY-lineBY, 2));
    } else {
        double ix = lineAX + u * (lineBX - lineAX);
        double iy = lineAY + u * (lineBY - lineAY);
        distance = sqrt(pow(circleCenterX-ix, 2) + pow(circleCenterY-iy, 2));
    }

    return distance < circleRadius;
}

bool RectInCircle(SDL_Rect rect, double rotation, pair<double, double> I, double r)
{
    double rectCenterX = rect.x + rect.w / 2;
    double rectCenterY = rect.y + rect.h / 2;
    double rectWidth = rect.w;
    double rectHeight = rect.h;

    double circleCenterX = I.fi;
    double circleCenterY = I.se;
    double circleRadius = r;

    double rectRotation = rotation;
    double tx, ty, cx, cy;

    if(rectRotation == 0) { // Higher Efficiency for Rectangles with 0 rotation.
        tx = circleCenterX;
        ty = circleCenterY;

        cx = rectCenterX;
        cy = rectCenterY;
    } else {
        tx = cos(rectRotation)*circleCenterX - sin(rectRotation)*circleCenterY;
        ty = cos(rectRotation)*circleCenterY + sin(rectRotation)*circleCenterX;

        cx = cos(rectRotation)*rectCenterX - sin(rectRotation)*rectCenterY;
        cy = cos(rectRotation)*rectCenterY + sin(rectRotation)*rectCenterX;
    }

    return PointInRect(rect, rectRotation, circleCenterX, circleCenterY) or
            SegmentInCircle(tx, ty, circleRadius, cx-rectWidth/2, cy+rectHeight/2, cx+rectWidth/2, cy+rectHeight/2) or
            SegmentInCircle(tx, ty, circleRadius, cx+rectWidth/2, cy+rectHeight/2, cx+rectWidth/2, cy-rectHeight/2) or
            SegmentInCircle(tx, ty, circleRadius, cx+rectWidth/2, cy-rectHeight/2, cx-rectWidth/2, cy-rectHeight/2) or
            SegmentInCircle(tx, ty, circleRadius, cx-rectWidth/2, cy-rectHeight/2, cx-rectWidth/2, cy+rectHeight/2);

}