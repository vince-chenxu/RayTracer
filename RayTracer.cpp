#include "RayTracer.h"

using namespace std;


RayTracer::RayTracer()
{
    threshold = 20;
}

void RayTracer::trace(Ray& ray, int depth, Color* color, vector<Primitive*> primitives, vector<Light> lights, float c0, float c1, float c2)
{
    if (depth > threshold)
    {
        // depth exceeds the threshold
        // Make the color black and return
        cout << "depth > threshold returning now\n";
        return;
    }

    LocalGeo local;
    Intersection in;
    float thit = 0.0f;
    BRDF brdf;
    Primitive* primitive = new AggregatePrimitive(primitives);
    if (!primitive->intersect(ray, &thit, &in))
    //if (!primitive->intersectP(ray))
    {
        // No intersection
        // Make the color black and return
        *color = Color(0.0f, 0.0f, 0.0f);
        return;
    }
    // there is intersection
    // get color
    in.primitive->getBRDF(in.localGeo, &brdf);
    color->r = brdf.ka.r;
    color->g = brdf.ka.g;
    color->b = brdf.ka.b;
    // color->print();
    // *color = Color(brdf.ka.r, brdf.ka.g, brdf.ka.b);

    // hardcode threshold
    if (depth == threshold) {
        // Finally add the ambient and emissive color to the object
        *color = *color + brdf.ka + brdf.ke;
    }

    // There is an intersection, loop through all light source
    for (int i = 0; i < lights.size(); i++)
    {
        Ray* lray;
        Color* lcolor;
        lights[i].generateLightRay(in.localGeo, lray, lcolor);

        // Check if the light is blocked or not

        // If not, do lighting calculation for this
        // light source

        if (!primitive->intersect(ray, &thit, &in)) {
            *color = *color + lighting(ray, in.localGeo, brdf, lray, lcolor, c0, c1, c2);
        }
        else {
            //*color = *color + shading(ray, in.localGeo, brdf, lray, lcolor);
        }
    }

    // Handle mirror reflection
    if (brdf.kr > 0) { //?????????????????/
        Ray reflectRay = createReflectRay(in.localGeo, ray);
        Color tempColor;
        // Make a recursive call to trace the reflected ray
        trace(reflectRay, depth+1, &tempColor, primitives, lights, c0, c1, c2);
        *color = *color + tempColor * brdf.kr;
    } else {
        // Finally add the ambient and emissive color to the object
        *color = *color + brdf.ka + brdf.ke;
    }
}

Color RayTracer::lighting(Ray& ray, LocalGeo& local, BRDF brdf, Ray* lray, Color* lcolor, float c0, float c1, float c2) {
    Vector temp = Vector();
    Vector normal = Vector(local.normal->x, local.normal->y, local.normal->z);

    float nDotL = temp.dot(normal, lray->dir);
    Vector diffuse = Vector(brdf.kd.r, brdf.kd.g, brdf.kd.b);
    Vector specular = Vector(brdf.ks.r, brdf.ks.g, brdf.ks.b);

    Vector distance = lray->pos - *local.pos;
    float r = sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
    Color after_attenu = *lcolor / (c0 + c1 * r + c2 * r * r);
    Vector lightcolor = Vector(after_attenu.r, after_attenu.g, after_attenu.b);

    Vector diffuse_light = Vector(diffuse.x * lightcolor.x, diffuse.y * lightcolor.y, diffuse.z * lightcolor.z);
    Vector lambert = diffuse_light * max(nDotL, 0.0f);

    Vector half = (ray.dir + lray->dir);
    half.normalize();
    float nDotH = temp.dot(normal, half);

    Vector spec_light = Vector(specular.x * lightcolor.x, specular.y * lightcolor.y, specular.z * lightcolor.z);
    Vector phong = spec_light * pow (max(nDotH, 0.0f), brdf.ksh);

    Vector finalcolor = lambert + phong;
    return Color(finalcolor.x, finalcolor.y, finalcolor.z);
}
//
// Color RayTracer::shading(Ray& ray, LocalGeo& local, BRDF brdf, Ray* lray, Color* lcolor) {
//     return;
// }

Ray RayTracer::createReflectRay(LocalGeo& local, Ray& ray) {
    // calculate normal vector
    Normal* normal = local.normal;
    Vector n = Vector(normal->x, normal->y, normal->z);

    // temp vector to use dot
    Vector temp = Vector();
    Vector n_ = n * temp.dot(n, ray.dir);

    // direction of reflected ray
    Vector dir = ray.dir + (n_ - ray.dir) * 2;
    dir.normalize();

    Point* pos = local.pos;
    Ray reflectRay = Ray(*pos, dir);

    return reflectRay;
}
