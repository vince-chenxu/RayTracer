#include "Light.h"
#include "PointLight.h"
#include <iostream>

using namespace std;

PointLight::PointLight()
{
    // empty
}

PointLight::PointLight(float x, float y, float z, float r, float g, float b) {
    pos = Point(x, y, z);
    color = Color(r, g, b);
    attenu_const = 1.0f;
    attenu_linear = 0.0f;
    attenu_quadra = 0.0f;
    isDir = false;
}

PointLight::PointLight(float x, float y, float z, float r, float g, float b, float constant, float linear, float quadratic) {
    pos = Point(x, y, z);
    color = Color(r, g, b);
    attenu_const = constant;
    attenu_linear = linear;
    attenu_quadra = quadratic;
}

Color PointLight::getColor()
{
    return color;
}
bool PointLight::getDir()
{
    return false;
}
Point PointLight::getPos(){
    return pos;
}

void PointLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {

    *lcolor = Color(color.r, color.g, color.b);

    // direction: intersection position TO LIGHT SOURCE
    Vector dir = pos - local.pos;
    float t_max = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    // std::cout << "t_max" << '\n';
    // std::cout << t_max << '\n';
    float t_min = 0.0f;
    // position: intersection position
    *lray = Ray(local.pos, dir, t_min, t_max);
}

// PointLight::~PointLight() {
//
// }
