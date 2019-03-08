#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"
using namespace std;

// parent class for triangle and sphere
class Triangle : public Shape
{
public:
    // The intersection with the ray at t outside the range [t_min, t_max]
    // should return false.

    // Test if ray intersects with the shape or not (in object space), if so,
    // return intersection point and normal
    bool intersect(Ray& ray, float* thit, LocalGeo* local);

    // Same as intersect, but just return whether there is any intersection or
    // not
    bool intersectP(Ray& ray);

};

#endif // TRIANGLE_H
