#ifndef RAYTRACER_H
#define RAYTRACER_H
using namespace std;

class RayTracer
{
public:
    void trace(Ray& ray, int depth, Color* color);

private:
    // member variables
    int threshold;

};

#endif // RAYTRACER_H
