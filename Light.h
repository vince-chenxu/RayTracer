using namespace std;

class Light
{
    // This is an abstract class that will generate a ray starting from
    // the position stored in local to the position of the light source.
    // You might want to consider creating 2 derived classes for
    // point light source and directional light source.
    // For directional light, the origin of the ray is the same,
    // and the ray points to the light direction, however, t_max is infinity.

public:
    void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor);   
};
