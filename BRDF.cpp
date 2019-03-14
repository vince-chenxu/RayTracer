#include "BRDF.h"

using namespace std;

BRDF::BRDF()
{

}
BRDF::BRDF(Color kd_v, Color ks_v, Color ka_v)
{
    // may need to implement copy constructor for Color class
    kd = kd_v;
    ks = ks_v;
    ka = ka_v;
}

BRDF::~BRDF()
{

}
