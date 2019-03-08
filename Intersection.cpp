#include "Intersection.h"

using namespace std;


// default constructor
Intersection::Intersection()
{

}
// constructor
Intersection::Intersection(LocalGeo geo, Shape* s)
{
    // may need to implement copy contructor for corresponding classes
    localGeo = geo;
    shape = s;
}
// destructor
Intersection::~Intersection()
{
    // ?
}
