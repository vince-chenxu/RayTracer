#include "Sample.h"
using namespace std;

// default constructor
Sample::Sample()
{
    x = y = 0; // default values for x, y
}

// constructor
Sample::Sample(float x_val, float y_val)
{
    x = x_val;
    y = y_val;
}

void Sample::print()
{
    cout << "Printing Sample coords: x: " << x << " y: " << y << endl; 
}
