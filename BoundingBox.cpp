#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "Point.h"
#include "Ray.h"
#include <iostream>

class BoundingBox
{
public:
    BoundingBox();
    BoundingBox(const Point &min, const Point &max);
    bool intersectP(const Ray &ray);
    Point min_pos, max_pos;
};
#endif // BOUNDINGBOX_H
