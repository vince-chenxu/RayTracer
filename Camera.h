//camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
#ifndef CAMERA_H
#define CAMERA_H
#include "Sample.h"
#include "Point.h"
#include "Ray.h"
#include <cfloat>
const float pi = 3.1415;
class Camera
{
public:
    // default constructor
	Camera();
	// Constructor
	Camera(Point from, Point at, Vector u, float fov, int w, int h);
    // Create a ray starting from the camera that passes through the
    // corresponding pixel (sample.x, sample.y) on the image plane.
    void generateRay(Sample& sample, Ray* ray);
private:
	// member variables
	Point lookFrom, lookAt;
	Vector up;
	float fovy;
	int width, height;
};

#endif // CAMERA_H
