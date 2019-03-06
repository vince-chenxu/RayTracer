#include "Material.h"
#include <iostream>

using namespace std;

void Material::getBRDF(LocalGeo& local, BRDF* brdf)
{
    return constantBRDF;
}
