#include "RayTracer.h"

using namespace std;


RayTracer::RayTracer()
{

}

void RayTracer::trace(Ray& ray, int depth, int max_depth, Color* color, vector<Primitive*> primitives, vector<Light*> lights, float c0, float c1, float c2)
{
    // std::cout << "prim_size: " << '\n';
    // std::cout << primitives.size() << '\n';
    // std::cout << "light_size: " << '\n';
    // std::cout << lights.size() << '\n';
    // std::cout << "depth" << '\n';
    // std::cout << depth << '\n';

    if (depth > max_depth)
    {
        // depth exceeds the threshold
        // Make the color black and return
        //cout << "depth > threshold returning now\n";
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
    //*color = Color(brdf.ka.r, brdf.ka.g, brdf.ka.b);
    // color->print();

    // std::cout << "primitive-normal" << '\n';
    // Vector test_normal = Vector(in.primitive->normal->x, in.primitive->normal->y, in.primitive->normal->z);
    // test_normal.print();

    // if (depth == max_depth) {
    //     // Finally add the ambient and emissive color to the object
    // }

    // Finally add the ambient and emissive color to the object
    *color = *color + brdf.ka + brdf.ke;

    // std::cout << "AE color" << '\n';
    // color->print();

    // There is an intersection, loop through all light source
    // cout << "light number" << '\n';
    // cout << lights.size() << '\n';
    for (int i = 0; i < lights.size(); i++)
    {
        Ray* lray = new Ray();
        Color* lcolor = new Color();
        lights[i]->generateLightRay(in.localGeo, lray, lcolor);

        // std::cout << "t_max" << '\n';
        // std::cout << lray->t_max << '\n';

        // std::cout << "lights property" << '\n';
        // lights[i]->getColor().print();
        //
        // std::cout << "lcolor" << '\n';
        // lcolor->print();

        Intersection temp_in;
        float temp_thit = 0.0f;

        // check if the light is blocked or not, if not, do lighting calculation for this light source
        Vector diff = lray->dir * (0.001);
        lray->pos.x = diff.x + lray->pos.x;
        lray->pos.y = diff.y + lray->pos.y;
        lray->pos.z = diff.z + lray->pos.z;
        //LocalGeo temp = LocalGeo(Point(in.localGeo.pos->x + diff.x, in.localGeo.pos->y + diff.y, in.localGeo.pos->z + diff.z), *in.localGeo.normal);

        // std::cout << "t_max" << '\n';
        // std::cout << lray->t_max << '\n';
        if (!primitive->intersectP(*lray)) {

            // directional VS point light
            if (!lights[i]->getDir()) {
                Vector dis = lights[i]->getPos() - in.localGeo.pos;
                float distance = sqrt(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
                // std::cout << "distance" << '\n';
                // std::cout << distance << '\n';

                *color = *color + lighting(ray, in.localGeo, brdf, lray, lcolor, c0, c1, c2, distance);
                // cout << "color when lighting" << '\n';
                // color->print();
                //??????????? does every light have its own attenuation or share the same one
            } else {
                *color = *color + lighting(ray, in.localGeo, brdf, lray, lcolor, 1.0f, 0.0f, 0.0f, 0.0f);
            }
        }
        else {
            //*color = *color + shading(ray, in.localGeo, brdf, lray, lcolor);
            // *color = Color(0.0f, 0.0f, 0.0f);
        }
    }

    Ray reflectRay = createReflectRay(in.localGeo, ray);
    Vector diff2 = reflectRay.dir * (0.001);
    reflectRay.pos.x = diff2.x + reflectRay.pos.x;
    reflectRay.pos.y = diff2.y + reflectRay.pos.y;
    reflectRay.pos.z = diff2.z + reflectRay.pos.z;
    Color tempColor = Color(0.0f, 0.0f, 0.0f);
    // Make a recursive call to trace the reflected ray
    trace(reflectRay, depth+1, max_depth, &tempColor, primitives, lights, c0, c1, c2);

    // std::cout << "tempColor: " << '\n';
    // tempColor.print();

    *color = *color + Color(tempColor.r * brdf.ks.r, tempColor.g * brdf.ks.g, tempColor.b * brdf.ks.b);


    // // Handle mirror reflection
    // Vector diff = ray.dir * (-0.0001); // + or - ?????????????????
    // LocalGeo temp = LocalGeo(Point(in.localGeo.pos->x + diff.x, in.localGeo.pos->y + diff.y, in.localGeo.pos->z + diff.z), *in.localGeo.normal);
    // Ray reflectRay = createReflectRay(temp, ray);
    // Color tempColor;
    // // Make a recursive call to trace the reflected ray
    // trace(reflectRay, depth+1, max_depth, &tempColor, primitives, lights, c0, c1, c2);
    // *color = *color + Color(tempColor.r * brdf.ks.r, tempColor.g * brdf.ks.g, tempColor.b * brdf.ks.b);

}

Color RayTracer::lighting(Ray& ray, LocalGeo& local, BRDF brdf, Ray* lray, Color* lcolor, float c0, float c1, float c2, float r) {
    // temp and normal vectors
    Vector temp = Vector();
    Vector normal = Vector(local.normal.x, local.normal.y, local.normal.z);
    // normal.normalize();
    // std::cout << "lcolor" << '\n';
    // lcolor->print();

    // std::cout << "lray-dir: " << '\n';
    // lray->dir.print();
    //
    // std::cout << "normal: " << '\n';
    // normal.print();

    // calculate N dot L and N dot H
    float nDotL = abs(temp.dot(normal, lray->dir));
    Vector half = (ray.dir * (-1) + lray->dir);
    half.normalize();
    float nDotH = abs(temp.dot(normal, half));

    // std::cout << "half: " << '\n';
    // half.print();
    //
    // std::cout << "nDotH: " << '\n';
    // std::cout << nDotH << '\n';
    //
    // std::cout << "nDotL: " << '\n';
    // std::cout << nDotL << '\n';

    // change diffuse and specular to vectors
    Vector diffuse = Vector(brdf.kd.r, brdf.kd.g, brdf.kd.b);
    Vector specular = Vector(brdf.ks.r, brdf.ks.g, brdf.ks.b);

    // std::cout << "diffuse_vector: " << '\n';
    // diffuse.print();

    // calculate the light color after attenuation
    // Vector distance = lray->pos - local.pos;
    // float r = sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
    Color after_attenu = *lcolor / (c0 + c1 * r + c2 * r * r);
    Vector lightcolor = Vector(after_attenu.r, after_attenu.g, after_attenu.b);

    // std::cout << "lcolor_: " << '\n';
    // lcolor->print();
    //
    // std::cout << "c0: " << '\n';
    // std::cout << c0 << '\n';
    // std::cout << "c1: " << '\n';
    // std::cout << c1 << '\n';
    // std::cout << "c2: " << '\n';
    // std::cout << c2 << '\n';

    // std::cout << "lightcolor: " << '\n';
    // lightcolor.print();

    // calculate lambert and phong
    Vector diffuse_light = Vector(diffuse.x * lightcolor.x, diffuse.y * lightcolor.y, diffuse.z * lightcolor.z);
    Vector lambert = diffuse_light * max(nDotL, 0.0f);
    //
    // std::cout << "lambert: " << '\n';
    // lambert.print();
    Vector spec_light = Vector(specular.x * lightcolor.x, specular.y * lightcolor.y, specular.z * lightcolor.z);
    Vector phong = spec_light * pow (max(nDotH, 0.0f), brdf.ksh);

    Vector finalcolor = lambert + phong;
    return Color(finalcolor.x, finalcolor.y, finalcolor.z);
    //return Color(lambert.x, lambert.y, lambert.z);
}

// Color RayTracer::shading(Ray& ray, LocalGeo& local, BRDF brdf, Ray* lray, Color* lcolor) {
//     return;
// }

Ray RayTracer::createReflectRay(LocalGeo& local, Ray& ray) {
    // calculate normal vector
    Normal normal = local.normal;
    Vector n = Vector(normal.x, normal.y, normal.z);

    // std::cout << "local normal" << '\n';
    // n.print();

    Vector dir = ray.dir * (-1);

    // std::cout << "ray dir" << '\n';
    // dir.print();

    // temp vector to use dot
    Vector temp = Vector();
    Vector n_ = n * temp.dot(n, dir);

    // direction of reflected ray
    Vector dir_ = dir + (n_ - dir) * 2;
    dir_.normalize();

    Point pos = local.pos;
    Ray reflectRay = Ray(pos, dir_);

    return reflectRay;
}

// Ray RayTracer::createReflectRay(LocalGeo& local, Ray& ray) {
//     // calculate normal vector
//     Normal normal = local.normal;
//     Vector n = Vector(normal.x, normal.y, normal.z);
//
//     // temp vector to use dot
//     Vector temp = Vector();
//     Vector n_ = n * temp.dot(n, ray.dir);
//
//     // direction of reflected ray
//     Vector dir = ray.dir + (n_ - ray.dir) * 2;
//     dir.normalize();
//
//     Point pos = local.pos;
//     Ray reflectRay = Ray(pos, dir);
//
//     return reflectRay;
// }
