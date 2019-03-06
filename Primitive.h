using namespace std;

class Primitive
{
public:
    //  Abstract class for primitives in the scene
    bool intersect(Ray& ray, float* thit, Intersection* in);
    bool intersectP(Ray& ray);
    void getBRDF(LocalGeo& local, BRDF* brdf);
};
