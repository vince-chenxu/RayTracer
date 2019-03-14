#include "Matrix.h"

using namespace std;

Matrix::Matrix()
{
    // empty
    // create identity matrix
    // for (int i = 0; i < 4; i ++)
    //     for (int j = 0; j < 4; j ++)
    //         mat[i][j] = 0;
    // mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 1;
    mat = glm::mat4(1.0f);
}
Matrix::Matrix(float x, float y, float z)
{
    // empty for now

}
void Matrix::rotate(float x, float y, float z, float degree)
{
    // Convert degree to radian
    float radians = degree * PI / 180;

    // Normalize the vector to unit vector
    Vector nAxis = Vector(x, y, z);
    nAxis.normalize();

    // Save (1 - cos(theta)) for readability
    float oneMinusCos = 1 - cos(radians);

    // Compute each element of the 3x3 matrix
    // mat[0][0] = cos(radians) + (nAxis.x * nAxis.x) * oneMinusCos;
    // mat[0][1] = (nAxis.x * nAxis.y) * oneMinusCos - nAxis.z * sin(radians);
    // mat[0][2] = nAxis.x * nAxis.z * oneMinusCos + (nAxis.y * sin(radians));
    // mat[0][3] = 0.0f;
    // mat[1][0] = nAxis.y * nAxis.x * oneMinusCos + nAxis.z * sin(radians);
    // mat[1][1] = cos(radians) + nAxis.y * nAxis.y * oneMinusCos;
    // mat[1][2] = nAxis.y * nAxis.z * oneMinusCos - nAxis.x * sin(radians);
    // mat[1][3] = 0.0f;
    // mat[2][0] = nAxis.z * nAxis.x * oneMinusCos - nAxis.y * sin(radians);
    // mat[2][1] = nAxis.z * nAxis.y * oneMinusCos + nAxis.x * sin(radians);
    // mat[2][2] = cos(radians) + nAxis.z * nAxis.z * oneMinusCos;
    // mat[2][3] = 0.0f;
    // mat[3][0] = 0.0f;
    // mat[3][1] = 0.0f;
    // mat[3][0] = 0.0f;
    // mat[3][3] = 1.0f;
    float mat11 = cos(radians) + (nAxis.x * nAxis.x) * oneMinusCos;
    float mat12 = (nAxis.x * nAxis.y) * oneMinusCos - nAxis.z * sin(radians);
    float mat13 = nAxis.x * nAxis.z * oneMinusCos + (nAxis.y * sin(radians));
    float mat14 = 0.0f;
    float mat21 = nAxis.y * nAxis.x * oneMinusCos + nAxis.z * sin(radians);
    float mat22 = cos(radians) + nAxis.y * nAxis.y * oneMinusCos;
    float mat23 = nAxis.y * nAxis.z * oneMinusCos - nAxis.x * sin(radians);
    float mat24 = 0.0f;
    float mat31 = nAxis.z * nAxis.x * oneMinusCos - nAxis.y * sin(radians);
    float mat32 = nAxis.z * nAxis.y * oneMinusCos + nAxis.x * sin(radians);
    float mat33 = cos(radians) + nAxis.z * nAxis.z * oneMinusCos;
    float mat34 = 0.0f;
    float mat41 = 0.0f;
    float mat42 = 0.0f;
    float mat43 = 0.0f;
    float mat44 = 1.0f;


    // Populate the 3x3 matrix
    mat = glm::mat4(mat11, mat12, mat13, mat14,
                    mat21, mat22, mat23, mat24,
                    mat31, mat32, mat33, mat34,
                    mat41, mat42, mat43, mat44);
    // Since it's column major, we transpose the matrix
    mat = glm::transpose(mat);
    // return result;
}
void Matrix::translate(float x, float y, float z)
{
    mat[3][0] = x;
    mat[3][1] = y;
    mat[3][2] = z;
}
void Matrix::scale(float x, float y, float z)
{
    mat[0][0] = mat[0][0] * x;
    mat[1][1] = mat[1][1] * y;
    mat[2][2] = mat[2][2] * z;
}
Matrix Matrix::inverse()
{
    mat = glm::inverse(mat);
    return *this;
}
Matrix Matrix::transpose()
{
    mat = glm::transpose(mat);
    return *this;
}
void Matrix::print()
{
    cout << "Printing 4x4 matrix:\n";
    cout << mat[0][0] << " " << mat[1][0] << " " << mat[2][0] << " " << mat[3][0] << endl
         << mat[0][1] << " " << mat[1][1] << " " << mat[2][1] << " " << mat[3][1] << endl
         << mat[0][2] << " " << mat[1][2] << " " << mat[2][2] << " " << mat[3][2] << endl
         << mat[0][3] << " " << mat[1][3] << " " << mat[2][3] << " " << mat[3][3] << endl;
}
