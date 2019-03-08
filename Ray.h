#ifndef RAY_H
#define RAY_H
#include "Point.h"
//using namespace std;

class Ray
{
public:
    // It represent the ray ray(t) = pos + t*dir, where t_min <= t <= t_max
    // default construc
    Ray();
    // constructor with Point position, Vector direction, min and max
    Ray(Point position, Vector direction, float min, float max);
    // destructor
    ~Ray();
private:
    Point pos;
    Vector dir;
    float t_min, t_max;
};


#endif // RAY_H
