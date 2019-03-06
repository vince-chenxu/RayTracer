#include "Intersection.h"
#include <iostream>
using namespace std;


// default constructor
Intersection::Intersection()
{

}
// constructor
Intersection::Intersection(LocalGeo geo, Primitive* prim)
{
    // may need to implement copy contructor for corresponding classes
    locaoGeo = geo;
    primitive = prim;
}
// destructor
Intersection::~Intersection()
{
    // ?
}
