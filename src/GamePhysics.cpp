#include "GamePhysics.h"


double distance(pair<double, double> a, pair<double,double> b){
    return sqrt((a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se));
}

double vector_length(pair<double, double> a){
    return sqrt(a.fi * a.fi + a.se * a.se);
}

double cos(pair<double,double> a, pair<double, double> b){
    double numerator = a.fi * b.fi + a.se * b.se;
    double denominator = vector_length(a) * vector_length(b);
    return numerator / denominator;
}

double sin(pair<double,double> a, pair<double, double> b){
    double numerator = a.fi * b.fi + a.se * b.se;
    numerator = (numerator < 0) ? -numerator : numerator;

    double denominator = vector_length(a) * vector_length(b);
    return numerator / denominator;

}
