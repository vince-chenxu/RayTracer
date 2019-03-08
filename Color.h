#ifndef COLOR_H
#define COLOR_H
#include <iostream>

using namespace std;

class Color
{
public:
    // Support +,- with other color
    // Support scalar *, /
    // May support conversion from xyz

    // default constructor
    Color();
    // constructor with float r, g, b
    Color(float red, float green, float blue);
    // overload + operator
    Color operator+(Color other);
    // overload - operator
    Color operator-(Color other);
    // overload * operator
    Color operator*(float scalar);
    // overload / operator
    Color operator/(float scalar);
    void print();
//private:
    float r, g, b;
};


#endif // COLOR_H
