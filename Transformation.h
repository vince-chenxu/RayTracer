#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
using namespace std;

class Transformation
{
    // Support Point, Vector, Normal, Ray, LocalGeo transformation by
    // operator * overloading
public:
    // default constructor
    Transformation();
    void rotate(float x, float y, float z, float degree);
    void translate(float x, float y, float z);
    void scale(float x, float y, float z);
private:
    // Matrix m and its inverse transpose minvt
    Matrix m, minvt;
    Point* p;
    Vector* v;
    Normal* n;
    Ray* r;
    LocalGeo* lg;
};


#endif // TRANSFORMATION_H
