#include "RayTracer.h"

using namespace std;


RayTracer::RayTracer()
{

}

void RayTracer::trace(Ray& ray, int depth, int max_depth, Color* color, vector<Primitive*> primitives, vector<Light> lights, float c0, float c1, float c2)
{
    if (depth > max_depth)
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
    // color->r = brdf.ka.r;
    // color->g = brdf.ka.g;
    // color->b = brdf.ka.b;
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

        // // check if the light is blocked or not, if not, do lighting calculation for this light source
        // // directional VS point light
        // Ray eyetolight;
        // if (lray->isDir) {
        //     eyetolight = new Ray(lray->pos, lray->dir * (-1));
        // } else {
        //     eyetolight = new Ray(in.localGeo.pos, lray->dir * (-1));
        // }

        if (!primitive->intersect(*lray, &thit, &in)) {
            *color = *color + lighting(ray, in.localGeo, brdf, lray, lcolor, c0, c1, c2);
        }
        else {
            //*color = *color + shading(ray, in.localGeo, brdf, lray, lcolor);
        }
    }

    // Handle mirror reflection
    Ray reflectRay = createReflectRay(in.localGeo, ray);
    Color tempColor;
    // Make a recursive call to trace the reflected ray
    trace(reflectRay, depth+1, max_depth, &tempColor, primitives, lights, c0, c1, c2);
    *color = *color + Color(tempColor.r * brdf.ks.r, tempColor.g * brdf.ks.g, tempColor.b * brdf.ks.b);

}

Color RayTracer::lighting(Ray& ray, LocalGeo& local, BRDF brdf, Ray* lray, Color* lcolor, float c0, float c1, float c2) {
    // temp and normal vectors
    Vector temp = Vector();
    Vector normal = Vector(local.normal->x, local.normal->y, local.normal->z);

    // calculate N dot L and N dot H
    float nDotL = temp.dot(normal, lray->dir);
    Vector half = (ray.dir + lray->dir);
    half.normalize();
    float nDotH = temp.dot(normal, half);

    // change diffuse and specular to vectors
    Vector diffuse = Vector(brdf.kd.r, brdf.kd.g, brdf.kd.b);
    Vector specular = Vector(brdf.ks.r, brdf.ks.g, brdf.ks.b);

    // calculate the light color after attenuation
    Vector distance = lray->pos - *local.pos;
    float r = sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
    Color after_attenu = *lcolor / (c0 + c1 * r + c2 * r * r);
    Vector lightcolor = Vector(after_attenu.r, after_attenu.g, after_attenu.b);

    // calculate lambert and phong
    Vector diffuse_light = Vector(diffuse.x * lightcolor.x, diffuse.y * lightcolor.y, diffuse.z * lightcolor.z);
    Vector lambert = diffuse_light * max(nDotL, 0.0f);
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
