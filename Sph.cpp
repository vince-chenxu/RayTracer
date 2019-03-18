#include "Sph.h"

Sph::Sph(float x_val, float y_val, float z_val, float r)
{
    x = x_val;
    y = y_val;
    z = z_val;
    radius = r;
}
void Sph::print()
{
    cout << "center x: " << x << " center y: " << y << " center z: " << z << " radius: " << radius << endl;
}
