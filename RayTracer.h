#ifndef RAYTRACER_H
#define RAYTRACER_H
#include "Intersection.h"
#include "Ray.h"
#include "Color.h"
#include "BRDF.h"
#include "Shape.h"
#include <vector>
#include <iostream>
using namespace std;

class RayTracer
{
public:
    void trace(Ray& ray, int depth, Color& color, vector<Shape*> shape);

private:
    // member variables
    int threshold;

};

#endif // RAYTRACER_H
