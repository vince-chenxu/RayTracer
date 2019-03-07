//camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov

class Camera
{
public:
    // default constructor
	Camera();
	// Constructor
	Camera(Point lookFrom, Point lookAt, Vector up, float fovy, int width, int height);
    // Create a ray starting from the camera that passes through the
    // corresponding pixel (sample.x, sample.y) on the image plane.
    void generateRay(Sample& sample, Ray* ray);

};
