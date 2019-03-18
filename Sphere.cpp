#include "Shape.h"
#include "Sphere.h"
#include <iostream>

using namespace std;

Sphere::Sphere()
{
    // empty for now
}
// constructor
Sphere::Sphere(float c1, float c2, float c3, float r, Color c)
{
    center = new Point(c1, c2, c3);
    radius = r;
    color = new Color(c.r, c.g, c.b);
}

// The intersection with the ray at t outside the range [t_min, t_max]
// should return false.

// Test if ray intersects with the shape or not (in object space), if so,
// return intersection point and normal
bool Sphere::intersect(Ray& ray, float* thit, LocalGeo* local) {
    Point e = ray.getPos();
    Vector d = ray.getDir();
    Vector e_vec = Vector(e.x, e.y, e.z);
    Vector c = Vector(center->x, center->y, center->z);

    float a_ = d.dot(d, d);
    float b_ = d.dot(d * (float)2, e_vec - c);
    float c_ = d.dot(e_vec - c, e_vec - c) - radius * radius;

    float d_ = b_ * b_ - 4 * a_ * c_;

    if (d_ < 0) {
        return false;
    }

    d_ = sqrt(d_);

    float t0 = (-1 * b_ - d_) / (2 * a_);
    float t1 = (-1 * b_ + d_) / (2 * a_);

    if (t1 > 0 && t0 > 0) {
        *thit = t0;
    }
    if (t1 < 0 && t0 < 0) {
        return false;
    }
    if (t0 == t1) {
        *thit = t0;
    }
    if (t0 < 0 && t1 > 0) {
        *thit = t1;
    }

    Vector p = e_vec + d * (*thit);
    local->pos = Point(p.x, p.y, p.z);

    Vector n = p - c;
    n.normalize();

    local->normal = Normal(n.x, n.y, n.z);
    // cout << "Sphere pos: \n";
    // local->pos.print();
    // cout << "Sphere normal:\n";
    // local->normal.print();
    return true;
}

// Same as intersect, but just return whether there is any intersection or
// not
bool Sphere::intersectP(Ray& ray) {
    float* thit;
    LocalGeo* local = new LocalGeo();
    return intersect(ray, thit, local);
}

void Sphere::print()
{
    // cout << "center coordinates: ";
    // center->print();
    // cout << "radius: " << radius << endl;
}

Color Sphere::getColor()
{
    return *color;
}
