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

    sample.x += 0.5f;
    sample.y += 0.5f;
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
    float beta = tan(angle) * (height/2.0 - sample.y)/(height/2.0);
    Vector temp = u * alpha + v * beta - a;

    temp.normalize();

    *ray = Ray(lookFrom, temp);

    // float alpha = tan(angle) * ((float)my_wdith/my_height) * (sample.x - my_wdith/2.0) / (my_wdith/2.0);
    // /*
    //  cout << "angle: " << angle << endl;
    //  cout << "width: " << my_wdith << endl;
    //  cout << "height: " << my_height << endl;
    //  cout << "sample: " << sample.x << " " << sample.y << endl;
    //  cout << "alpha: " << alpha << endl;
    //  */
    // float beta = tan(angle) * (my_height/2.0 - sample.y) / (my_height/2.0);
    // //cout << "beta: " << beta << endl;
    // Point p0(my_eye.x, my_eye.y, my_eye.z);
    // Vector p1 = my_u*alpha + my_v*beta - my_w;
    //
    // //my_u.show();
    //
    // p1.normalization();
    // *ray = Ray(p0, p1, 0.0f, FLT_MAX);
}
