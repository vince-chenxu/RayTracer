#include "RayTracer.h"

using namespace std;


RayTracer::RayTracer()
{
    threshold = 20;
}
void RayTracer::trace(Ray& ray, int depth, Color* color, vector<Shape*> shape)
{
    // hardcode threshold

    if (depth > threshold)
    {
        // depth exceeds the threshold
        // Make the color black and return
        *color = Color(0.0f, 0.0f, 0.0f);
        cout << "depth > threshold returning now\n";
        return;
    }
    LocalGeo in;
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
    bool intersected = false;
    // here we loop through all shapes
    //cout << "about to loop through all shapes\n";
    float min = 99999999;
    int shape_index = 0;
    for (int i = 0; i < shape.size(); i ++)
    {
        // here check for the min distance
        if (shape[i]->intersect(ray, &thit, &in))
        {

            // No intersection
            // Make the color black and return
            //cout << "shape #" << i + 1 << " intersected with ray" << endl;
            if (min > thit)
            {
                min = thit;
                shape_index = i;
            }
            //*color = Color(0.5f, 0.5f, 0.5f);
            intersected = true;
        }
        //else
            //cout << "no intersection at shape #" << i + 1 << endl;

    }
    // no intersection
    if (!intersected)
    {
        *color = Color(0.0f, 0.0f, 0.0f);
        //cout << "No intersection\n";
    }
    else
    {
        //cout << "Yes intersection\n";
        *color = Color(shape[shape_index]->getColor().r, shape[shape_index]->getColor().g, shape[shape_index]->getColor().b);
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
