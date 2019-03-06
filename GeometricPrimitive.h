using namespace std;

class GeometricPrimitive
{
public:
    GeometricPrimitive();
    GeometricPrimitive(Transformation objW, Transformation wObj, Shape* s, Material* m);
    bool intersect(Ray& ray, float* thit, Intersection* in);
    bool intersectP(Ray& ray);
    void getBRDF(LocalGeo& local, BRDF* brdf);
private:
    Transformation objToWorld, worldToObj;
    Shape* shape;
    Material* mat;
};
