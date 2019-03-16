#include "RayTracer.h"

using namespace std;


RayTracer::RayTracer()
{
    threshold = 20;
}

void RayTracer::trace(Ray& ray, int depth, Color* color, vector<Primitive*> primitives, vector<Light> lights)
{
    // hardcode threshold

    if (depth > threshold)
    {
        // depth exceeds the threshold
        // Make the color black and return
        cout << "depth > threshold returning now\n";
        return;
    }
    LocalGeo local;
    // Intersection in;
    // float thit = 0.0f;
    BRDF brdf;
    Primitive* primitive = new AggregatePrimitive(primitives);
    // if (!primitive->intersect(ray, &thit, &in))
    if (!primitive->intersectP(ray))
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

    // There is an intersection, loop through all light source
    for (i = 0; i < lights.size(); i++)
    {
        Ray* lray;
        Color* lcolor;
        lights[i].generateLightRay(in.localGeo, &lray, &lcolor);

        // Check if the light is blocked or not

        // If not, do lighting calculation for this
        // light source
        if (!primitive->intersectP(lray)) {
            *color += lighting(ray, in.localGeo, brdf, lray, lcolor);
        }
        else {
            *color += shading(ray, in.localGeo, brdf, lray, lcolor);
        }
    }

    // Handle mirror reflection
    if (brdf.kr > 0) {
        Ray reflectRay = createReflectRay(in.localGeo, ray);
        Color tempColor;
        // Make a recursive call to trace the reflected ray
        trace(reflectRay, depth+1, &tempColor, primitives, lights);
        *color += brdf.kr * tempColor; // ??????????
    }
}

Color RayTracer::lighting(Ray& ray, LocalGeo& local, BRDF brdf, Ray* lray, Color* lcolor) {
    float nDotL = dot(local.normal, lray->dir);
    Vector temp = Vector();
    Vector lightcolor = Vector(lcolor->r, lcolor->g, lcolor->b);
    Vector diffuse = Vector(kd.r, kd.g, kd.b);
    Vector specular = Vector(ks.r, ks.g, ks.b);
    // Vector ambient = Vector(ka.r, ka.g, ka.b);

    Vector lambert = diffuse * lightcolor * max(nDotL, 0.0);

    Vector half = (ray.dir + lray->dir).normalize();
    float nDotH = temp.dot(local.normal, half);

    Vector phong = specular * lightcolor * pow (max(nDotH, 0.0), myshininess); // ?????????

    Vector finalcolor = lambert + phong;
    return Color(finalcolor.r, finalcolor.g, finalcolor.b);
}

Color RayTracer::shading(LocalGeo& local, BRDF brdf, Ray* lray, Color* lcolor) {

}

Ray RayTracer::createReflectRay(LocalGeo& local, Ray ray) {
    // calculate normal vector
    Normal normal = local.normal;
    Vector n = Vector(normal.x, normal.y, normal.z);

    // temp vector to use dot
    Vector temp = Vector();
    Vector n' = temp.dot(n, ray.dir) * n;

    // direction of reflected ray
    Vector dir = ray.dir + 2 * (n' - ray.dir);
    dir.normalize();

    Point pos = local.pos;
    Ray reflectRay = Ray(pos, dir);

    return reflectRay;
}

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
