using namespace std;

class Normal
{
public:
    // Constructor from 3 floats
    // Support +, -
    // Note: Need to be normalized after operations (Be careful for 0 vector)
    
    // default constructor
    Normal();
    // constructor with 3 floats
    Normal(float x_val, float y_val, float z_val);
private:
    float x, y, z;
};