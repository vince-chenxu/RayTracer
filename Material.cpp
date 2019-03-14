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

BRDF Material::getBRDF(LocalGeo& local, BRDF* brdf)
{
    return constantBRDF;
}
