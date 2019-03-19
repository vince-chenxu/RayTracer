#include "Light.h"
#include "DirectionalLight.h"
#include <iostream>

using namespace std;

DirectionalLight::DirectionalLight()
{
    // constructor
}

DirectionalLight::DirectionalLight(float x, float y, float z, float r, float g, float b) {
    dir = Vector(x, y, z);
    color = Color(r, g, b);
    dir.normalize();
    // std::cout << "lcolor in DirectionalLight.cpp" << '\n';
    // color.print();
    attenu_const = 1.0f;
    attenu_linear = 0.0f;
    attenu_quadra = 0.0f;
    isDir = true;
}

DirectionalLight::DirectionalLight(float x, float y, float z, float r, float g, float b, float constant, float linear, float quadratic) {
    dir = Vector(x, y, z);
    color = Color(r, g, b);
    dir.normalize();
    attenu_const = constant;
    attenu_linear = linear;
    attenu_quadra = quadratic;
}

Color DirectionalLight::getColor()
{
    return color;
}
bool DirectionalLight::getDir()
{
    return true;
}
Point DirectionalLight::getPos() {
    return Point(0.0f, 0.0f, 0.0f);
}

void DirectionalLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {
    *lcolor = Color(color.r, color.g, color.b);
    // direction: intersection position TO LIGHT SOURCE
    Vector ray_dir = Vector(dir.x, dir.y, dir.z);
    // ray_dir.normalize();

    // position: intersection position

    *lray = Ray(local.pos, ray_dir);
}


// DirectionalLight::~DirectionalLight() {
//
// }
