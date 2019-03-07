using namespace std;

class Scene
{
public:
    // default contructor
    Scene();
    // constructor with single const char* filename
    Scene(const char* filename);
    // helper function for loadFromFile
    bool readvals (stringstream &s, const int numvals, float* values);
    // function to readfile
    void loadFromFile(const char* fileName);
    // function for the main rendering loop
    void render();
// private member variables
private:
    // width and height of the window/scene
    int width, height;
    // pointers to Point objects: lookFrom, lookAt
    Point* lookFrom, lookAt,
    // pointer to Vector object: up
    Vector* up;
    // fov
    float fov;
    // pointers to Color objects: ka, kd, ks
    Color* ka, kd, ks;
    
};
