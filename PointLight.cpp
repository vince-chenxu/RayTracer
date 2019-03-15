#include "Light.h"
#include "PointLight.h"
#include <iostream>

using namespace std;

PointLight::PointLight()
{
    // empty
}

PointLight::PointLight(int x, int y, int z, float r, float g, float b) {
    pos = Point(x, y, z);
    color = Color(r, g, b);
    attenu_const = 1;
    attenu_linear = 0;
    attenu_quadra = 0;
}

PointLight::PointLight(int x, int y, int z, float r, float g, float b, float constant, float linear, float quadratic) {
    pos = Point(x, y, z);
    color = Color(r, g, b);
    attenu_const = constant;
    attenu_linear = linear;
    attenu_quadra = quadratic;
}

void PointLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {
    lcolor = new Color(color.r, color.g, color.b);
    Vector dir = pos - *local.pos;
    dir.normalize();
    lray = new Ray(*local.pos, dir);
}
