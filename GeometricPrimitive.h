#ifndef GEOMETRICPRIMITIVE_H
#define GEOMETRICPRIMITIVE_H
#include "Primitive.h"
#include "Transformation.h"
#include "Shape.h"
#include "Material.h"
#include "Intersection.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "BRDF.h"
#include <iostream>

using namespace std;

class GeometricPrimitive : public Primitive
{
public:
    GeometricPrimitive();
    GeometricPrimitive(Transformation objW, Transformation wObj, Shape* s, Material* m);
    ~GeometricPrimitive();
    bool intersect(Ray& ray, float* thit, Intersection* in);
    bool intersectP(Ray& ray);
    void getBRDF(LocalGeo& local, BRDF* brdf);
// private:
    Transformation objToWorld, worldToObj;
    Shape* shape;
    Material* mat;
};


#endif // GEOMETRICPRIMITIVE_H
