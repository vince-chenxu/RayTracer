#include "LocalGeo.h"
#include <iostream>

using namespace std;

// default constructor
LocalGeo::LocalGeo()
{
    // empty for now
    pos = Point();
    normal = Normal();
}
// constructor
LocalGeo::LocalGeo(Point p, Normal n)
{
    // may need to implement copy constructors
    pos = p;
    normal = n;
}
LocalGeo::~LocalGeo()
{

}
