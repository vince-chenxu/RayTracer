#ifndef AggregatePrimitive_H
#define AggregatePrimitive_H
#include "Primitive.h"
#include "Intersection.h"
using namespace std;

class AggregatePrimitive : public Primitive
{
public:
    // Constructor store the STL vector of pointers to primitives.
    // Intersect just loops through all the primitives in the list and
    // call the intersect routine. Compare thit and return that of the nearest
    // one (because we want the first hit).
    // Also, the in->primitive should be set to the pointer to that primitive.
    // When you implement acceleration structure, it will replace this class
    AggregatePrimitive();
    AggregatePrimitive(vector<Primitive*> list);
    ~AggregatePrimitive();
    bool intersect(Ray& ray, float* thit, Intersection* in);
    bool intersectP(Ray& ray);
    void getBRDF(LocalGeo& local, BRDF* brdf)
    {
        exit(1);
        // This should never get called, because in->primitive will
        // never be an aggregate primitive
    }
    float getDist(const Point& p, const Point& r);
// private:
    vector<Primitive*> primitives;
};


#endif // AggregatePrimitive_H
