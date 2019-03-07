#include "Vector.h"
#include <iostream>

using namespace std;

Vector::Vector()
{
    // empty for now
}

Vector::Vector(float x_val, float y_val, float z_val)
{
    x = x_val;
    y = y_val;
    z = z_val;
}

// destructor
Vector::~Vector()
{
    // called automatically by the system
}
// overload + operator
Vector::Vector operator+(Vector other)
{
    return Vector(x + other.x, y + other.y, z + other.z);
}
// overload - operator
Vector::Vector operator-(Vector other)
{
    return Vector(x - other.x, y - other.y, z - other.z);
}
// overload * operator
Vector::Vector operator*(float scalar)
{
    return Vector(x * scalar, y * scalar, z * scalar);
}
// overload / operator
Vector operator/(float scalar)
{
    // here we assume scalar != 0, may need to implement error checking later
    return Vector(x / scalar, y / scalar, z / scalar);
}

// normalize function
void Vector::normalize()
{
    float divisor = sqrt(x * x + y * y + z * z);
    if (divisor != 0.0f)
    {
        x = x / divisor;
        y = y / divisor;
        z = z / divisor;
    }
}

Vector::Vector cross(const Vector& left, const Vector& right)
{
    vec3 leftV = vec3(left.x, left.y, left.z);
    vec3 rightV = vec3(right.x, right.y, right.z);
    vec3 w = glm::cross(leftV, rightV);
    return Vector(w.x, w.y, w.z);

}
