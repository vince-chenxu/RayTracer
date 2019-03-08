#ifndef SHAPE_H
#define SHAPE_H

#include "Ray.h"
#include "LocalGeo.h"
using namespace std;

// parent class for triangle and sphere
class Shape
{
public:
    // Triangle and Sphere are probably best implemented here
    // The intersection with the ray at t outside the range [t_min, t_max]
    // should return false.

    // Test if ray intersects with the shape or not (in object space), if so,
    // return intersection point and normal
    // virtual bool intersect(Ray& ray, float* thit, LocalGeo* local);
    //
    // // Same as intersect, but just return whether there is any intersection or
    // // not
    // virtual bool intersectP(Ray& ray);
    virtual bool intersect(Ray& ray, float* thit, LocalGeo* local) = 0;

    // Same as intersect, but just return whether there is any intersection or
    // not
    virtual bool intersectP(Ray& ray) = 0;
    virtual void print();

};

#endif // SHAPE_H
