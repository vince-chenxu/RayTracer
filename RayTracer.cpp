#include "RayTracer.h"
#include <iostream>
using namespace std;

void RayTracer::trace(Ray& ray, int depth, Color* color)
{
    if (depth exceed some threshold)
    {
        Make the color black and return
    }
    if (!primitive.intersect(ray, &thit, &in)
    {
        // No intersection
        Make the color black and return
    }
    // Obtain the brdf at intersection point
    in.primitive->getBRDF(in.local, &brdf);

    // There is an intersection, loop through all light source
    for (i = 0; i < #lights; i++)
    {
        lights[i].generateLightRay(in.local, &lray, &lcolor);

        // Check if the light is blocked or not
        if (!primitive->intersectP(lray))
        // If not, do shading calculation for this
        // light source
        *color += shading(in.local, brdf, lray, lcolor);
    }

    // Handle mirror reflection
    if (brdf.kr > 0)
    {
        reflectRay = createReflectRay(in.local, ray);

        // Make a recursive call to trace the reflected ray
        trace(reflectRay, depth+1, &tempColor);
        *color += brdf.kr * tempColor;
    }
}
