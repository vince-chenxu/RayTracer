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
    Vector a = lookAt - lookFrom;
    // normalize a to get w
    a.normalize();
    // calculate u
    Vector u;
    u = u.cross(up, a);
    u.normalize();
    // calculate v
    Vector v;
    v = v.cross(a, u);
    // calculate fovx with the given fovy
    // tan(fovx/2) = tan(foy/2) * width/height
    float fovx = 2 * atan(tan(fovy / 2) * width / height);
    // alpha = tan(fovx/2)*((j-(width/2))/(width/2))
    float alpha = tan(fovx/2)*((sample.x-(width/2))/(width/2));
    // float beta = tan(fovy/2)*((height/2-i)/(height/2))
    float beta = tan(fovy/2)*((height/2-sample.y)/(height/2));
    // ray = eye + (alpha*u + beta*v - w)/abs(alpha*u + beta*v - w)
    Vector temp1 = u * alpha;
    Vector temp2 = v * beta;
    Vector temp3 = temp1 + temp2;
    Vector temp4 = temp3 - a;
    temp4.normalize();
    //*ray = (lookAt - lookFrom) + temp4;
    ray = new Ray(lookFrom, temp4, 0, 100);
}
