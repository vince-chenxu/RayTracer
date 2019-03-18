#include "Tri.h"
using namespace std;

Tri::Tri(int x_val, int y_val, int z_val)
{
    x = x_val;
    y = y_val;
    z = z_val;
}

void Tri::print()
{
    cout << "Vertex1: " << x << " Vertex2: " << y << " Vertex3: " << z << endl;
}
