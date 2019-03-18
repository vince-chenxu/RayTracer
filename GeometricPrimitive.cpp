#include "GeometricPrimitive.h"

GeometricPrimitive::GeometricPrimitive()
{

}
GeometricPrimitive::GeometricPrimitive(Transformation objW, Transformation wObj, Shape* s, Material* m)
{
    // implement copy constructors
    objToWorld = objW;
    worldToObj = wObj;
    shape = s;
    mat = m;
}
GeometricPrimitive::~GeometricPrimitive()
{

}
bool GeometricPrimitive::intersect(Ray& ray, float* thit, Intersection* in)
{
    Ray oray = worldToObj*ray;
     oray.t_max = ray.t_max;
    LocalGeo olocal;
    if (!shape->intersect(oray, thit, &olocal))
        return false;
    // cout << "olocal in GeometricPrimitive\n";
    // olocal.print();
    in->primitive = this;
    in->localGeo = objToWorld*olocal;
    // cout << "localGeo in GeometricPrimitive\n";
    // in->localGeo.print();
    return true;
}
bool GeometricPrimitive::intersectP(Ray& ray)
{
    Ray oray = worldToObj*ray;
    oray.t_max = ray.t_max;
    return shape->intersectP(oray);
}
void GeometricPrimitive::getBRDF(LocalGeo& local, BRDF* brdf)
{
    mat->getBRDF(local, brdf);
}
