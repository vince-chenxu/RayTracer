#ifndef MATRIX_H
#define MATRIX_H

using namespace std;

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
    //void transpose();
private:
    // 4x4 matrix
    glm::mat4 m = glm::mat4(1.0f);
};


#endif // MATRIX_H
