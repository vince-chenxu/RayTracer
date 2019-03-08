// cpp files
// #include "Point.h"
#include "Film.h"
#include "Camera.h"

#include "Sampler.h"
// #include "Color.h"
// #include "Ray.h"
// #include "Film.h"


// useful libraries
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Scene
{
public:
    // default contructor
    Scene();
    // constructor with single const char* filename
    Scene(const char* filename);
    // helper function for loadFromFile
    bool readvals (stringstream &s, const int numvals, string values[]);
    // function to readfile
    void loadFromFile(const char* fileName);
    // function for the main rendering loop
    void render();
// private member variables
private:
    // // width and height of the window/scene
    int width, height;
    // pointers to Point objects: lookFrom, lookAt
    Point* lookFrom;
    Point* lookAt;
    // pointer to Vector object: up
    Vector* up;
    // fov
    float fov;
    // pointers to Color objects: ka, kd, ks
    Color* ka;
    Color* kd;
    Color* ks;
    // film object pointer
    Film* film;
    // Sampler object pointer
    Sampler* sampler;
    Sample* sample;
    Ray* ray;
    Color* color;
    Camera* camera;
};
