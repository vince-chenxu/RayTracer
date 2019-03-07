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
Camera(Point lookFrom, Point lookAt, Vector up, float fovy, int width, int height)
{
    Vector a = lookAt - lookFrom;
    // normalize a to get w
    a.normalize();
    // calculate u
    Vector u = u.cross(up, a);
    u.normalize();
    // calculate v
    Vector v = v.cross(a, u);
    // calculate fovx with the given fovy
    // tan(fovx/2) = tan(foy/2) * width/height
    float fovx = 2 * atan(tan(fovy / 2) * width / height);
    // float alpha = tan(fovx/2)*((j-(width/2))/(width/2))
    // float beta = tan(fovy/2)*((height/2-i)/(height/2))
    // ray = eye + (alpha*u + beta*v - w)/abs(alpha*u + beta*v - w)
}

void Camera::generateRay(Sample& sample, Ray* ray)
{

}
