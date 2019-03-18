#ifndef LIGHT_P
#define LIGHT_P

#include "Light.h"
#include "Ray.h"
#include "LocalGeo.h"
#include "Color.h"

using namespace std;

class PointLight: public Light
{
public:
    PointLight();
    // ~PointLight();
    PointLight(int x, int y, int z, float r, float g, float b);
    PointLight(int x, int y, int z, float r, float g, float b, float constant, float linear, float quadratic);
    Color getColor();
    bool getDir();
    void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor);
    Point getPos();

// private:
    Point pos;
    Color color;
    float attenu_const;
    float attenu_linear;
    float attenu_quadra;
    bool isDir;
};

#endif
