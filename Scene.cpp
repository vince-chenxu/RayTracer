#include "Scene.h"
#include <iostream>

using namespace std;

// main function
int main(int argc, char* argv[])
{
    Scene scene;
    scene.
}

// main render function
void Scene::render()
{
    while (!sampler.generateSample(&sample)
    {
        camera.generateRay(sample, &ray);
        raytracer.trace(ray, &color);
        film.commit(sample, color);
    }
    film.writeImage();
}
