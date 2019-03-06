#include "Shape.h"
#include <iostream>

using namespace std;

// Test if ray intersects with the shape or not (in object space), if so,
// return intersection point and normal
bool Shape::intersect(Ray& ray, float* thit, LocalGeo* local)
{
    // add code here
}

// Same as intersect, but just return whether there is any intersection or
// not
bool Shape::intersectP(Ray& ray)
{
    // add code here
}
