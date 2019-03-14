// cpp files
// #include "Point.h"
#include "Film.h"
#include "Camera.h"
//#include "Shape.h"
#include "Sampler.h"
#include "Vertex.h"
#include "Tri.h"
#include "Sph.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Shape.h"
#include "RayTracer.h"
#include "Matrix.h"
#include "Primitive.h"
#include "Material.h"
#include "GeometricPrimitive.h"
#include "Transformation.h"
// #include "BRDF.h"
// #include "Color.h"
// #include "Ray.h"
// #include "Film.h"


// useful libraries
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

class Scene
{
public:
    // default contructor
    Scene();
    // constructor with single const char* filename
    Scene(const char* filename);
    // helper function for loadFromFile
    bool readvals (stringstream &s, const int numvals, float values[]);
    // function to readfile
    void loadFromFile(const char* fileName);
    // function for the main rendering loop
    void render();
    // helper functions from hw2
    // void matransform(stack<glm::mat4> &transfstack, float* values);
    void rightmultiply(const glm::mat4 & M, stack<Matrix> &transfstack);

// private member variables
private:
    // // width and height of the window/scene
    int width, height, maxverts;
    // pointers to Point objects: lookFrom, lookAt
    Point* lookFrom;
    Point* lookAt;
    // pointer to Vector object: up
    Vector* up;
    // fov
    float fov;
    // Color objects: ka, kd, ks
    Color ka, kd, ks;
    // Color* kd;
    // Color* ks;
    // film object pointer
    Film* film;
    // Sampler object pointer
    Sampler* sampler;
    Sample sample;
    Ray ray;
    Color color;
    Camera* camera;
    // vector that holds all vertices
    vector<Vertex> vertex;
    // vector that holds all triangle coords
    vector<Tri> tri;
    // vector that holds all sphere coords with radius
    vector<Sph> sph;
    // vector that holds all shapes
    vector<Shape*> shape;
    RayTracer raytracer;
    // vector that holds all primitives
    vector<Primitive*> primitives;
};
