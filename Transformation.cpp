#include "Transformation.h"
#include <iostream>

using namespace std;

Transformation::Transformation()
{
    // empty for now
    m = Matrix();
    minvt = m.inverse().transpose();
}

Transformation::Transformation(Matrix matrix)
{
    m = matrix;
    // this may cause problem
    minvt = m.inverse().transpose();
}
Transformation::~Transformation()
{

}
Point Transformation::operator*(const Point &point)
{
    float x = m.mat[0][0] * point.x + m.mat[1][0] * point.y + m.mat[2][0] * point.z + m.mat[3][0] * 1.0f;
    float y = m.mat[0][1] * point.x + m.mat[1][1] * point.y + m.mat[2][1] * point.z + m.mat[3][1] * 1.0f;
    float z = m.mat[0][2] * point.x + m.mat[1][2] * point.y + m.mat[2][2] * point.z + m.mat[3][2] * 1.0f;
    return Point(x, y, z);
}
Vector Transformation::operator*(const Vector &vector)
{
    float x = m.mat[0][0] * vector.x + m.mat[1][0] * vector.y + m.mat[2][0] * vector.z + m.mat[3][0] * 0.0f;
    float y = m.mat[0][1] * vector.x + m.mat[1][1] * vector.y + m.mat[2][1] * vector.z + m.mat[3][1] * 0.0f;
    float z = m.mat[0][2] * vector.x + m.mat[1][2] * vector.y + m.mat[2][2] * vector.z + m.mat[3][2] * 0.0f;
    return Vector(x, y, z);
}
Normal Transformation::operator*(const Normal &normal)
{
    // float x = minvt.mat[0][0] * normal.x + minvt.mat[1][0] * normal.y + minvt.mat[2][0] * normal.z + minvt.mat[3][0] * 0.0f;
    // float y = minvt.mat[0][1] * normal.x + minvt.mat[1][1] * normal.y + minvt.mat[2][1] * normal.z + minvt.mat[3][1] * 0.0f;
    // float z = minvt.mat[0][2] * normal.x + minvt.mat[1][2] * normal.y + minvt.mat[2][2] * normal.z + minvt.mat[3][2] * 0.0f;
    Vector v = Vector(normal.x, normal.y, normal.z);
    Transformation t = Transformation(minvt);
    v = t * v;
    v.normalize();
    return Normal(v.x, v.y, v.z);
}
LocalGeo Transformation::operator*(const LocalGeo &localGeo)
{
    // return LocalGeo((*this) * (*localGeo.pos), (*this) * (*localGeo.normal));
    LocalGeo local(localGeo.pos, localGeo.normal);
    local.pos = (*this) * localGeo.pos;
    local.normal = (*this) * localGeo.normal;
    return local;
}
Ray Transformation::operator*(const Ray &ray)
{
    return Ray((*this) * ray.pos, (*this) * ray.dir);
}
