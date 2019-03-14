#ifndef MATRIX_H
#define MATRIX_H
#include "Vector.h"
#include <iostream>
#include <cmath>

using namespace std;
const float PI = 3.1415926;
class Matrix
{
public:
    // Support creation of rotation, translation, scaling matrices
    // May support matrix inversion if needed
    // Also could support SVD, or other matrix decomposition, for future extension

    // default constructor
    Matrix();
    Matrix(float x, float y, float z);
    void rotate(float x, float y, float z, float degree);
    void translate(float x, float y, float z);
    void scale(float x, float y, float z);
    Matrix transpose();
    Matrix inverse();
    void print();
    //void transpose();
//private:
    // 4x4 matrix
    // float mat[4][4];
    glm::mat4 mat;
};


#endif // MATRIX_H
