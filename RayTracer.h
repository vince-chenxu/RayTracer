#ifndef RAYTRACER_H
#define RAYTRACER_H
#include "Intersection.h"
#include "Ray.h"
#include "Color.h"
#include "BRDF.h"
#include "Shape.h"
#include "LocalGeo.h"
#include "AggregatePrimitive.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class RayTracer
{
public:
    RayTracer();
    void trace(Ray& ray, int depth, int max_depth, Color* color, vector<Primitive*> primitives, vector<Light*> lights, float c0, float c1, float c2);
    Ray createReflectRay(LocalGeo& local, Ray& ray);
    Color lighting(Ray& ray, LocalGeo& local, BRDF brdf, Ray* lray, Color* lcolor, float c0, float c1, float c2, float r);
    Color shading(Ray& ray, LocalGeo& local, BRDF brdf, Ray* lray, Color* lcolor);

private:
    // member variables
    int threshold;

};

#endif // RAYTRACER_H
