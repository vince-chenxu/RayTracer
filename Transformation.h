#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include "Point.h"
#include "Normal.h"
#include "Vector.h"
#include "LocalGeo.h"
#include "Ray.h"
#include "Matrix.h"
using namespace std;

class Transformation
{
    // Support Point, Vector, Normal, Ray, LocalGeo transformation by
    // operator * overloading
public:
    // default constructor
    Transformation();
    Transformation(Matrix matrix);
    ~Transformation();
    // void rotate(float x, float y, float z, float degree);
    // void translate(float x, float y, float z);
    // void scale(float x, float y, float z);
    Point operator*(const Point &point);
    Vector operator*(const Vector &vector);
    Normal operator*(const Normal &normal);
    LocalGeo operator*(const LocalGeo &localGeo);
    Ray operator*(const Ray &ray);
// private:
    // Matrix m and its inverse transpose minvt
    Matrix m, minvt;
    // Point* p;
    // Vector* v;
    // Normal* n;
    // Ray* r;
    // LocalGeo* lg;
};


#endif // TRANSFORMATION_H
