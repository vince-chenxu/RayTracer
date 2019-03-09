#ifndef SPHERE_H
#define SPHERE_H
#include "Shape.h"
#include "Color.h"
using namespace std;

// parent class for triangle and sphere
class Sphere : public Shape
{
public:
    Sphere();
    // constructor
    Sphere(float c1, float c2, float c3, float r, Color c);
    // The intersection with the ray at t outside the range [t_min, t_max]
    // should return false.

    // Test if ray intersects with the shape or not (in object space), if so,
    // return intersection point and normal
    bool intersect(Ray& ray, float* thit, LocalGeo* local);

    // Same as intersect, but just return whether there is any intersection or
    // not
    bool intersectP(Ray& ray);
    Color getColor();
    void print();
// private:
    Point* center;
    float radius;
    Color* color;
};

#endif // SPHERE_H
