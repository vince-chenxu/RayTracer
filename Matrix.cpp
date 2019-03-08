#include "Matrix.h"
#include <iostream>

using namespace std;

Matrix::Matrix()
{
    // empty
}
Matrix::Matrix(float x, float y, float z)
{
    // empty for now
}
void Matrix::rotate(float x, float y, float z, float degree)
{
    glm::vec3 myRotationAxis(x, y, z);
    m = glm::rotate(degree, myRotationAxis);
}
void Matrix::translate(float x, float y, float z)
{
    m = glm::translate(glm::mat4(), glm::vec3(x, y, z);
}
void Matrix::scale(float x, float y, float z)
{
    m = glm::scale(x, y, z);
}
