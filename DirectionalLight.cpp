#include "Light.h"
#include "DirectionalLight.h"
#include <iostream>

using namespace std;

DirectionalLight::DirectionalLight()
{
    // constructor
}

DirectionalLight::DirectionalLight(int x, int y, int z, float r, float g, float b) {
    dir = Vector(x, y, z);
    color = Color(r, g, b);
    attenu_const = 1;
    attenu_linear = 0;
    attenu_quadra = 0;
    isDir = true;
}

DirectionalLight::DirectionalLight(int x, int y, int z, float r, float g, float b, float constant, float linear, float quadratic) {
    dir = Vector(x, y, z);
    color = Color(r, g, b);
    attenu_const = constant;
    attenu_linear = linear;
    attenu_quadra = quadratic;
}

void DirectionalLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {
    lcolor = new Color(color.r, color.g, color.b);

    // direction: intersection position TO LIGHT SOURCE
    Vector ray_dir = Vector(-dir.x, -dir.y, -dir.z);
    ray_dir.normalize();

    // position: intersection position
    lray = new Ray(*local.pos, ray_dir, 0, INFINITY);
}
