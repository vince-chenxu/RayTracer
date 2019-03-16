#include "BRDF.h"

using namespace std;

BRDF::BRDF()
{

}
BRDF::BRDF(Color kd_v, Color ks_v, Color ka_v, float ksh_, Color ke_v, float kr_)
{
    // may need to implement copy constructor for Color class
    kd = kd_v;
    ks = ks_v;
    ka = ka_v;
    ksh = ksh_;
    ke = ke_v;
    kr = kr_;
}

BRDF::~BRDF()
{

}
