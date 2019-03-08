#include "Transformation.h"
#include <iostream>

using namespace std;

Transformation::Transformation()
{
    // empty for now
}
void Transformation::rotate(float x, float y, float z, float degree)
{
    m.rotate(x, y, z, degree);
    minvt.rotate(x, y, z, -degree);
}
void Transformation::translate(float x, float y, float z)
{
    m.translate(x, y, z);
    minvt.translate(-x, -y, -z);
}
void Transformation::scale(float x, float y, float z)
{
    m.scale(x, y, z);
    minvt.scale(1/x, 1/y, 1/z);
}
