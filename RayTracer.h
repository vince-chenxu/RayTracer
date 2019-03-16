#ifndef RAYTRACER_H
#define RAYTRACER_H
#include "Intersection.h"
#include "Ray.h"
#include "Color.h"
#include "BRDF.h"
#include "Shape.h"
#include "LocalGeo.h"
#include "AggregatePrimitive.h"
#include <vector>
#include <iostream>
using namespace std;

class RayTracer
{
public:
    RayTracer();
    void trace(Ray& ray, int depth, Color* color, vector<Primitive*> primitives, vector<Light> lights);
    Ray createReflectRay(LocalGeo local, Ray ray);

private:
    // member variables
    int threshold;

};

#endif // RAYTRACER_H
