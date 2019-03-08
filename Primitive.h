#ifndef PRIMITIVE_H
#define PRIMITIVE_H
using namespace std;

class Primitive
{
public:
    //  Abstract class for primitives in the scene
    virtual bool intersect(Ray& ray, float* thit, Intersection* in);
    virtual bool intersectP(Ray& ray);
    virtual void getBRDF(LocalGeo& local, BRDF* brdf);
};


#endif // PRIMITIVE_H
