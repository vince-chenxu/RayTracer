#include "Normal.h"

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

// destructor
Normal::~Normal()
{
    // automatically called
}

// overload + operator
Normal Normal::operator+(Normal other)
{
    return Normal(x + other.x, y + other.y, z + other.z);
}
// overload - operator
Normal Normal::operator-(Normal other)
{
    return Normal(x - other.x, y - other.y, z - other.z);
}
// normalize function
void Normal::normalize()
{
    float divisor = sqrt(x * x + y * y + z * z);
    if (divisor != 0.0f)
    {
        x = x / divisor;
        y = y / divisor;
        z = z / divisor;
    }
}

void Normal::print()
{
    cout << "nx: " << x << " ny: " << y << " nz: " << z << endl;
}
