#ifndef BRDF_H
#define BRDF_H
#include "Color.h"
#include <iostream>
using namespace std;

class BRDF
{
public:
    // default contructor
    BRDF();
    // contructor
    BRDF(Color kd_v, Color ks_v, Color ka_v, float ksh_, Color ke_v);
    ~BRDF();
    // member variables
    // Storing information enough for shading
    // (it is not the actual BRDF function
    // in the rendering equation that will be covered later in the semester)
    Color kd, ks, ka, ke;
    float ksh;
};


#endif // BRDF_H
