#include "Light.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "Color.h"

using namespace std;

class DirectionalLight: public Light
{
public:
    DirectionalLight();
    DirectionalLight(int x, int y, int z, float r, float g, float b);
    DirectionalLight(int x, int y, int z, float r, float g, float b, float constant, float linear, float quadratic);
    Color getColor();
    bool getDir();
    void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor);

// private:
    Vector dir;
    Color color;
    float attenu_const;
    float attenu_linear;
    float attenu_quadra;
    bool isDir;
};
