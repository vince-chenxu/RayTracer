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
    //~Vector();
private:
    float x, y, z;
};
