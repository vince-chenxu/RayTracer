#include "BRDF.h"
#include <iostream>

using namespace std;

BRDF::BRDF(Color kd_v, Color ks_v, Color ka_v, Color kr_v)
{
    // may need to implement copy constructor for Color class
    kd = kd_v;
    ks = ks_v;
    ka = ka_v;
    kr = kr_v;
}

BRDF::~BRDF()
{
    
}
