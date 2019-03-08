#include "RayTracer.h"

using namespace std;

void RayTracer::trace(Ray& ray, int depth, Color& color, vector<Shape*> shape)
{
    if (depth > threshold)
    {
        // depth exceeds the threshold
        // Make the color black and return
        color = Color(0.0f, 0.0f, 0.0f);
        return;
    }
    Intersection in;
    BRDF brdf;
    float thit;
    //if (!primitive.intersect(ray, &thit, &in)
    // if (!shape.intersect(ray, &thit, &in))
    // {
    //     // No intersection
    //     // Make the color black and return
    //     *color = Color(0.0f, 0.0f, 0.0f);
    //     return;
    // }

    // here we loop through all shapes
    for (int i = 0; i < shape.size(); i ++)
    {
        // here check for the min distance
        if (!shape[i]->intersect(ray, &thit, &in))
        {
            // No intersection
            // Make the color black and return
            color = Color(0.0f, 0.0f, 0.0f);
            return;
        }

    }

    // Obtain the brdf at intersection point
    // in.primitive->getBRDF(in.local, &brdf);
    //in.shape->getBRDF(in.local, &brdf);
    // IMPORTANT: how to access BRDF and emission?

    // Then color it to be ambient + emission


    // Below is for light:

    // There is an intersection, loop through all light source
    // for (i = 0; i < #lights; i++)
    // {
    //     lights[i].generateLightRay(in.local, &lray, &lcolor);
    //
    //     // Check if the light is blocked or not
    //     if (!primitive->intersectP(lray))
    //     // If not, do shading calculation for this
    //     // light source
    //     *color += shading(in.local, brdf, lray, lcolor);
    // }
    //
    // // Handle mirror reflection
    // if (brdf.kr > 0)
    // {
    //     reflectRay = createReflectRay(in.local, ray);
    //
    //     // Make a recursive call to trace the reflected ray
    //     trace(reflectRay, depth+1, &tempColor);
    //     *color += brdf.kr * tempColor;
    // }
}
