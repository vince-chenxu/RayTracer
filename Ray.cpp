#include "Ray.h"
#include <iostream>

using namespace std;

// default construc
Ray::Ray()
{
    // empty for now
}

Ray::Ray(Point position, Vector direction)
{
    pos = position;
    dir = direction;
    dir.normalize();
    t_min = 0.0f;
    t_max = FLT_MAX;
    // std::cout << "max" << '\n';
    // std::cout << t_max << '\n';
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
    // std::cout << "max" << '\n';
    // std::cout << t_max << '\n';
}

Point Ray::getPos() {
    return pos;
}

Vector Ray::getDir() {
    return dir;
}

float Ray::getMax() {
    std::cout << "max" << '\n';
    std::cout << t_max << '\n';
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

void Ray::print()
{
    // cout << "pos: ";
    // pos.print();
    // cout << "dir: ";
    // dir.print();
    // cout << "t_min: " << t_min << " t_max " << t_max << endl;
}
