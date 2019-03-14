#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Shape.h"
#include "LocalGeo.h"
#include "Primitive.h"
#include <iostream>
using namespace std;

class Intersection
{
public:
    // default constructor
    Intersection();
    // constructor
    // Intersection(LocalGeo geo, Primitive* prim);
    Intersection(LocalGeo geo, Shape* s);
    // destructor
    ~Intersection();

//private:
    // member varaible
    LocalGeo localGeo;
    Primitive* primitive;
    Shape* shape;
};

#endif // INTERSECTION_H
