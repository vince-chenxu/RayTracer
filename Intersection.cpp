#include "Intersection.h"
#include <iostream>
using namespace std;


// default constructor
Intersection::Intersection()
{

}
// constructor
Intersection::Intersection(LocalGeo geo, Shape* s)
{
    // may need to implement copy contructor for corresponding classes
    locaoGeo = geo;
    shape = s;
}
// destructor
Intersection::~Intersection()
{
    // ?
}
