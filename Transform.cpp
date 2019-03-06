// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
  // YOUR CODE FOR HW2 HERE
  // Please implement this.  Likely the same as in HW 1.

  // Convert degree to radian
  float radians = degrees * pi / 180;

  // Normalize the vector to unit vector
  vec3 nAxis = glm::normalize(axis);

  // Save (1 - cos(theta)) for readability
  float oneMinusCos = 1 - cos(radians);

  // Compute each element of the 3x3 matrix
  float mat11 = cos(radians) + (nAxis.x * nAxis.x) * oneMinusCos;
  float mat12 = (nAxis.x * nAxis.y) * oneMinusCos - nAxis.z * sin(radians);
  float mat13 = nAxis.x * nAxis.z * oneMinusCos + (nAxis.y * sin(radians));
  float mat21 = nAxis.y * nAxis.x * oneMinusCos + nAxis.z * sin(radians);
  float mat22 = cos(radians) + nAxis.y * nAxis.y * oneMinusCos;
  float mat23 = nAxis.y * nAxis.z * oneMinusCos - nAxis.x * sin(radians);
  float mat31 = nAxis.z * nAxis.x * oneMinusCos - nAxis.y * sin(radians);
  float mat32 = nAxis.z * nAxis.y * oneMinusCos + nAxis.x * sin(radians);
  float mat33 = cos(radians) + nAxis.z * nAxis.z * oneMinusCos;

  // Populate the 3x3 matrix
  mat3 result = mat3(mat11, mat12, mat13,
             mat21, mat22, mat23,
             mat31, mat32, mat33);
  // Since it's column major, we transpose the matrix
  result = glm::transpose(result);
  return result;
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.

  // Call rotate to compute the rotationMatrix
  mat3 rotationMatrix = rotate(degrees, up);
  // Compute eye and up
  eye = rotationMatrix * eye;
  up = rotationMatrix * up;
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.

  // Cross product up eye
  vec3 w = glm::cross(up, eye);
  // Call rotate to compute the rotationMatrix
  mat3 rotationMatrix = rotate(-degrees, w);
  // Compute eye and up
  eye = rotationMatrix * eye;
  up = rotationMatrix * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{

  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.

  // Normalize each vectors w u v
  vec3 w = glm::normalize(eye);
  vec3 u = glm::normalize(glm::cross(up,eye));
  vec3 v = glm::normalize(glm::cross(w,u));
  // Populate the resulting 4x4 matrix
  mat4 result = mat4(u.x, u.y, u.z, glm::dot(u, -eye),
             v.x, v.y, v.z, glm::dot(v, -eye),
             w.x, w.y, w.z, glm::dot(w, -eye),
               0,   0,   0,                1);
  // Transpose the matrix since it is column major
  result = glm::transpose(result);
  return result;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.
  mat4 ret(0);

  // Calculate the scale using the given fomula
  float scale = 1 / tan(fovy * 0.5 * pi / 180);
  // Scale x coordinates
  ret[0][0] = scale / aspect;
  // Scale y coordinates
  ret[1][1] = scale;
  // Remapping z to [0,1]
  ret[2][2] = -zFar / (zFar - zNear);
  // Remapping z [0,1]
  ret[3][2] = -zFar * zNear * 2.0f / (zFar - zNear);
  // Set w to -1
  ret[2][3] = -1;
  ret[3][3] = 0;
  // Return result
  return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
  // YOUR CODE FOR HW2 HERE
  // Implement scaling
  mat4 ret = mat4(sx, 0,  0, 0,
                  0, sy,  0, 0,
                  0,  0, sz, 0,
                  0,  0,  0, 1);
  ret = glm::transpose(ret);
  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{

  // YOUR CODE FOR HW2 HERE
  // Implement translation
  mat4 ret = mat4(1, 0,  0, tx,
                  0, 1,  0, ty,
                  0, 0,  1, tz,
                  0, 0,  0, 1);
  ret = glm::transpose(ret);
  return ret;
}

// To normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
  vec3 x = glm::cross(up,zvec);
  vec3 y = glm::cross(zvec,x);
  vec3 ret = glm::normalize(y);
  return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
