#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

class Vector
{
public:
    // Constructor from 3 floats
    // Support vector +, -
    // Support scalar *,/
    // Support normalization
    // Point – Point = Vector

    // default constructor
    Vector();
    // Constructor
    Vector(float x_val, float y_val, float z_val);
    // destructor
    ~Vector();
    // overload + operator
    friend Vector operator +(const Vector& left, const Vector& right);
    //Vector operator+(Vector other);
    // overload - operator
    friend Vector operator -(const Vector& left, const Vector& right);
    //Vector operator-(Vector other);
    // overload * operator
    Vector operator*(float scalar);
    // overload / operator
    Vector operator/(float scalar);
    // normalize function
    void normalize();
    Vector cross(const Vector& left, const Vector& right);
    void print();
// private:
    float x, y, z;
};


#endif // VECTOR_H
