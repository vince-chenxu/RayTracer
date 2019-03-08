#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"
using namespace std;

// parent class for triangle and sphere
class Triangle : public Shape
{
public:
    Triangle();
    Triangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3);
    // The intersection with the ray at t outside the range [t_min, t_max]
    // should return false.

    // Test if ray intersects with the shape or not (in object space), if so,
    // return intersection point and normal
    bool intersect(Ray& ray, float* thit, LocalGeo* local);

    // Same as intersect, but just return whether there is any intersection or
    // not
    bool intersectP(Ray& ray);

private:
    Point* v1;
    Point* v2;
    Point* v3;

};

#endif // TRIANGLE_H
