#include "Normal.h"
#include <iostream>

using namespace std;

// default constructor
Normal::Normal()
{
    // empty for now
}
// constructor with 3 floats
Normal::Normal(float x_val, float y_val, float z_val)
{
    x = x_val;
    y = y_val;
    z = z_val;
}
