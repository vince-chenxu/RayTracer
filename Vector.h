#include <vector>
#include <cmath>
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
    Vector operator+(Vector other);
    // overload - operator
    Vector operator-(Vector other);
    // overload * operator
    Vector operator*(float scalar);
    // overload / operator
    Vector operator/(float scalar);
    // normalize function
    void normalize();
    Vector cross(const Vector& left, const Vector& right);

private:
    float x, y, z;
};
