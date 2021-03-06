#include "Shape.h"
#include "Triangle.h"
#include <iostream>

using namespace std;

Triangle::Triangle()
{
    // empty for now
}
// constructor
Triangle::Triangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, Color c)
{
    v1 = new Point((float) x1, (float) y1, (float) z1);
    v2 = new Point((float) x2, (float) y2, (float) z2);
    v3 = new Point((float) x3, (float) y3, (float) z3);
    color = new Color(c.r, c.g, c.b);;
}
// Test if ray intersects with the shape or not (in object space), if so,
// return intersection point and normal
bool Triangle::intersect(Ray& ray, float* thit, LocalGeo* local)
{
    // std::cout << "t_max" << '\n';
    // std::cout << ray.t_max << '\n';
    // add code here
    Point pos = ray.getPos();
    Vector dir = ray.getDir();

    Vector p = pos - *v1;
    Vector v31 = *v3 - *v1;
    Vector v21 = *v2 - *v1;
    Vector n1 = dir.cross(dir, v21);
    Vector n2 = p.cross(p, v31);
    // divisor
    float d = n1.dot(n1, v31);
    if (d == 0.0f)
        return false;
    float temp = n2.dot(n2, v21);
    temp = temp / d;
    float b = n1.dot(n1, p);
    b = b / d;
    float g = n2.dot(n2, dir);
    g = g / d;

    if (b < 0.0f || b > 1.0f || g < 0.0f || g > 1.0f || (b + g) > 1.0f || temp < ray.getMin() || temp > ray.t_max) {
        // std::cout << "t_max" << '\n';
        // std::cout << ray.t_max << '\n';
        // if (ray.t_max < 10) {
        //     std::cout << "t_max" << '\n';
        //     std::cout << ray.t_max << '\n';
        // }
        return false;
    }

    // update thit
    *thit = temp;
    Vector n = v31.cross(v31, v21);
    n.normalize();

    local->pos = Point(pos.x + temp * dir.x, pos.y + temp * dir.y, pos.z + temp * dir.z);
    local->normal = Normal(n.x, n.y, n.z);
    // cout << "Triangle pos: \n";
    // local->pos.print();
    // cout << "Triangle normal:\n";
    // local->normal.print();
    return true;

}

// Same as intersect, but just return whether there is any intersection or
// not
bool Triangle::intersectP(Ray& ray)
{
    // add code here
    float thit;
    LocalGeo local;
    return intersect(ray, &thit, &local);
}
void Triangle::print()
{
    cout << "Vertex1: ";
    v1->print();
    cout << "Vertex2: ";
    v2->print();
    cout << "Vertex3: ";
    v3->print();
}

Color Triangle::getColor()
{
    return *color;
}
