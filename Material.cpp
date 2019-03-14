#include "Material.h"
#include <iostream>

using namespace std;

Material::Material()
{

}
Material::Material(BRDF brdf)
{
    constantBRDF = brdf;
}

void Material::getBRDF(LocalGeo& local, BRDF* brdf)
{
    *brdf = constantBRDF;
}
