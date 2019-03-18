#include "AggregatePrimitive.h"
#include <iostream>

using namespace std;


AggregatePrimitive::AggregatePrimitive()
{

}
AggregatePrimitive::~AggregatePrimitive()
{

}
AggregatePrimitive::AggregatePrimitive(vector<Primitive*> list)
{
    primitives = list;
}
bool AggregatePrimitive::intersect(Ray& ray, float* thit, Intersection* in)
{
    bool intersected = false;
    // here we loop through all primitives
    //cout << "about to loop through all primitives\n";
    // arbitrary big number, used for infinity, will replace later
    float min = FLT_MAX;
    for (int i = 0; i < primitives.size(); i ++)
    {
        float hit;
        Intersection n;
        if (primitives[i]->intersect(ray, &hit, &n))
        {
            // There is an intersection
            intersected = true;
            float dist = getDist(n.localGeo.pos, ray.pos);
            if (dist < min && hit > 0)
            {
                // update variables
                min = dist;
                *thit = hit;
                *in = n;

                // std::cout << "AggregatePrimitive normal: " << '\n';
                // Vector test_normal = Vector(in->localGeo.normal->x, in->localGeo.normal->y, in->localGeo.normal->z);
                // test_normal.print();
            }
        }
    }
    return intersected;
}
bool AggregatePrimitive::intersectP(Ray& ray)
{
    float thit;
    Intersection in;
    return intersect(ray, &thit, &in);
}

float AggregatePrimitive::getDist(const Point& p, const Point& r)
{
    return sqrt((p.x - r.x) * (p.x - r.x) + (p.y - r.y) * (p.y - r.y) + (p.z - r.z) * (p.z - r.z));
}
