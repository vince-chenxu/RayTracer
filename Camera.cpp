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
    // Vector xinc = u*2*tan(fovy*pi/180/2)/width * width/height;
    // Vector yinc = v*2*tan(fovy*pi/180/2)/height;
    // Vector vec = a + yinc*0.5*(2*sample.y+1-height) + xinc*0.5*(2*sample.x+1-width);
    // vec.normalize();
    // cout << "about to calculate angle\n";
    float angle = (fovy * pi / 180.0) / 2.0;
    // cout << "finished calculating angle\n";
    // calculate fovx with the given fovy
    // tan(fovx/2) = tan(foy/2) * width/height
    //float fovx = 2 * atan(tan(fovy / 2.0) * width / height);
    // alpha = tan(fovx/2)*((j-(width/2))/(width/2))
    float alpha = tan(angle) * (width/float(height))*(sample.x-width/2.0)/(width/2.0);
    //cout << "fovy: " << fovy << " width: " << width << " height: " << height << endl;
    //cout << "sample: ";
    //sample.print();
    //cout << "alpha: " << alpha << endl;
    // cout << "alpha done\n";
    // float beta = tan(fovy/2)*((height/2-i)/(height/2))
    float beta = tan(angle) * (height/2.0-sample.y)/(height/2.0);
    //cout << "beta: " << beta << endl;
    // ray = eye + (alpha*u + beta*v - w)/abs(alpha*u + beta*v - w)
    // Vector temp1 = u * alpha;
    // Vector temp2 = v * beta;
    // Vector temp3 = temp1 + temp2;
    // Vector temp4 = temp3 - a;
    // temp4.normalize();
    Vector temp = u * alpha + v * beta - a;

    temp.normalize();
    //cout << "direction: ";
    //temp.print();
    //*ray = (lookAt - lookFrom) + temp4;

    *ray = Ray(lookFrom, temp, 1, 100);
}
