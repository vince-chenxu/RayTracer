#include "Camera.h"
#include <iostream>
#include <cmath>

using namespace std;

// default constructor
Camera::Camera()
{
    // empty for now
}

// Constructor
Camera::Camera(Point from, Point at, Vector u, float fov, int w, int h)
{
    lookFrom = from;
    lookAt = at;
    up = u;
    fovy = fov;
    width = w;
    height = h;
}

void Camera::generateRay(Sample& sample, Ray* ray)
{

    // a = eye
    Vector a = lookFrom - lookAt;
    // normalize a to get w
    a.normalize();
    // calculate u
    Vector u;
    u = u.cross(up, a);
    u.normalize();
    // calculate v
    Vector v;
    v = v.cross(a, u);
    float angle = (fovy * pi / 180.0) / 2.0;
    float alpha = tan(angle) * (width/float(height))*(sample.x-width/2.0)/(width/2.0);
    float beta = tan(angle) * (sample.y-height/2.0)/(height/2.0);
    Vector temp = u * alpha + v * beta - a;

    temp.normalize();

    *ray = Ray(lookFrom, temp, 1, 1000);
}
