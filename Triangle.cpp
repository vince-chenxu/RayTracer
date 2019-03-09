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
    // add code here
    Point pos = ray.getPos();
    Vector dir = ray.getDir();

    Vector v31 = *v3 - *v1;
    Vector v21 = *v2 - *v1;
    Vector n = v31.cross(v31, v21);
    n.normalize();

    // Need to have dot function in Vector class, also Point dot Vector
    Vector pos_vec = Vector(pos.x, pos.y, pos.z);

    // V31, v1->x, v1->y, v1->z
    float temp1 = v31.dot(Vector(v1->x, v1->y, v1->z), n);
    float temp2 = v31.dot(pos_vec, n);
    float temp3 = v31.dot(dir, n);

    *thit = (temp1 - temp2) / temp3;

    if (*thit > ray.getMax() || *thit < ray.getMin()) {
        return false;
    }

    Vector p = pos_vec + dir * (*thit);
    Vector vt_1 = Vector(v1->x, v1->y, v1->z);
    Vector vt_2 = Vector(v2->x, v2->y, v2->z);
    Vector vt_3 = Vector(v3->x, v3->y, v3->z);
    Point p_point = Point(p.x, p.y, p.z);

    // Vector cur1 = p_point - *v1;
    // Vector cur2 = *v2 - *v1;
    // Vector cur3 = *v3 - *v1;
    Vector cur1 = p - vt_1;
    Vector cur2 = vt_2 - vt_1;
    Vector cur3 = vt_3 - vt_1;

    // float r = (cur1.x * cur2.y - cur1.y * cur2.x) / (cur3.x * cur2.y - cur2.x * cur3.y);
    // float b = (cur1.x - r * cur3.x) / cur2.x;
    float b = (cur1.x*cur3.y - cur1.y*cur3.x) / (cur2.x*cur3.y - cur2.y*cur3.x);
    float r = (cur1.x*cur2.y - cur1.y*cur2.x) / (cur3.x*cur2.y - cur3.y*cur2.x);

    if ((b >= 0.0 && b <= 1.0) && (r >= 0.0 && r <= 1.0) && (r + b) <= 1.0)
    {
        local->pos = new Point(p.x, p.y, p.z);
        local->normal = new Normal(n.x, n.y, n.z);

        return true;
    }

    return false;
    // if (beta < 0 || beta > 1)
    //     return false;
    // if (gamma < 0 || gamma > 1)
    //     return false;
    // if ((beta + gamma) > 1)
    //     return false;
    //
    // local->pos = new Point(p.x, p.y, p.z);
    // local->normal = new Normal(n.x, n.y, n.z);
    //
    // return true;
}

// Same as intersect, but just return whether there is any intersection or
// not
bool Triangle::intersectP(Ray& ray)
{
    // add code here
    float* thit;
    LocalGeo* local = new LocalGeo();
    return intersect(ray, thit, local);
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
