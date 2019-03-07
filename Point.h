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
    friend Point operator +(const Point& left, const Point& right);
    // overload - operator
    friend Point operator -(const Point& left, const Point& right);
private:
    float x, y , z;
};
