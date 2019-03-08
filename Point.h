#ifndef POINT_H
#define POINT_H
#include "Vector.h"
#include <iostream>
using namespace std;

class Point
{
public:
    // Constructor from 3 floats
    // Support +,- with vector

    // default constructor
    Point();
    // constructor with 3 floats
    Point(float x_val, float y_val, float z_val);
    // overload + operator
    friend Point operator +(const Point& other);
    // overload - operator
    friend Vector operator -(const Point& left, const Point& right);
    // print the coordinates x y z
    void print();
//private:
    float x, y, z;
};


#endif // POINT_H
