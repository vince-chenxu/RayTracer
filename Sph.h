#ifndef SPH_H
#define SPH_H
#include <iostream>
using namespace std;

class Sph
{
public:
    Sph(float x_val, float y_val, float z_val, float r);
    void print();
    float x, y, z, radius;
};
#endif // SPH_H
