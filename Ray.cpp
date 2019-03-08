#include "Ray.h"
#include <iostream>

using namespace std;

// default construc
Ray::Ray()
{
    // empty for now
}
// constructor with Point position, Vector direction, min and max
Ray::Ray(Point position, Vector direction, float min, float max)
{
    pos = position;
    dir = direction;
    // normalize direction
    dir.normalize();
    t_min = min;
    t_max = max;
}

Point Ray::getPos() {
    return pos;
}

Vector Ray::getDir() {
    return dir;
}

float Ray::getMax() {
    return t_max;
}
float Ray::getMin() {
    return t_min;
}
// destructor
Ray::~Ray()
{
    // automatically called
}
