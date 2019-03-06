#include "Point.h"
#include <iostream>

using namespace std;

// default constructor
Point::Point()
{
    // empty for now
}
// constructor with 3 floats
Point::Point(float x_val, float y_val, float z_val)
{
    x = x_val;
    y = y_val;
    z = z_val;
}
