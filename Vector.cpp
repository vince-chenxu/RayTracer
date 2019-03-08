#include "Vector.h"

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
Vector operator +(const Vector& left, const Vector& right)
{
    return Vector(left.x + right.x, left.y + right.y, left.z + right.z);
}
// overload - operator
Vector operator -(const Vector& left, const Vector& right)
{
    return Vector(left.x - right.x, left.y - right.y, left.z - right.z);
}
// overload * operator
Vector Vector::operator*(float scalar)
{
    return Vector(x * scalar, y * scalar, z * scalar);
}
// overload / operator
Vector Vector::operator/(float scalar)
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

Vector Vector::cross(const Vector& left, const Vector& right)
{
    glm::vec3 leftV = glm::vec3(left.x, left.y, left.z);
    glm::vec3 rightV = glm::vec3(right.x, right.y, right.z);
    glm::vec3 w = glm::cross(leftV, rightV);
    return Vector(w.x, w.y, w.z);

}

void Vector::print()
{
    cout << "x: " << x << " y: " << y << " z: " << z << endl;
}
