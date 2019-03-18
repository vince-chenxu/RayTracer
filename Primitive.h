#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "Ray.h"
#include "BRDF.h"
#include "LocalGeo.h"
using namespace std;

class Intersection;

class Primitive
{
public:
    //  Abstract class for primitives in the scene
    virtual bool intersect(Ray& ray, float* thit, Intersection* in) = 0;
    virtual bool intersectP(Ray& ray) = 0;
    virtual void getBRDF(LocalGeo& local, BRDF* brdf) = 0;
};


#endif // PRIMITIVE_H
