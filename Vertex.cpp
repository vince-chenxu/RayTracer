#include "Vertex.h"
using namespace std;

Vertex::Vertex(int x_val, int y_val, int z_val)
{
    x = x_val;
    y = y_val;
    z = z_val;
}

void Vertex::print()
{
    cout << "x: " << x << " y: " << y << " z: " << z << endl;
}
