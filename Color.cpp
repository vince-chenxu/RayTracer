#include "Color.h"

using namespace std;

// default constructor
Color::Color()
{
    // empty for npw
}

// constructor with float r, g, b
Color::Color(float red, float green, float blue)
{
    r = red;
    g = green;
    b = blue;
}
// overload + operator
Color Color::operator+(Color other)
{
    return Color(r + other.r, g + other.g, b + other.b);
}
// overload - operator
Color Color::operator-(Color other)
{
    return Color(r - other.r, g - other.g, b - other.b);
}
// overload * operator
Color Color::operator*(float scalar)
{
    r *= scalar;
    g *= scalar;
    b *= scalar;
    return *this;
}
// overload / operator
Color Color::operator/(float scalar)
{
    if (scalar != 0.0f)
    {
        r /= scalar;
        g /= scalar;
        b /= scalar;
    }
    // return here to prevent no return value warning, r g b values will not be
    // modified if scalar is 0
    return *this;
}

void Color::print()
{
    cout << "r: " << r << " g: " << g << " b: " << b << endl;
}
