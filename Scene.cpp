// header files
#include "Scene.h"

using namespace std;

Scene::Scene()
{
    // default constructor empty for now
}

Scene::Scene(const char* filename)
{
    // set default values
    maxdepth = 5;
    ka = Color(0.2, 0.2, 0.2);
    attenu_const = 1.0f;
    attenu_linear = 0.0f;
    attenu_quadra = 0.0f;
    // pass the filename and begin command parsing process
    loadFromFile(filename);
    render();
}

// The function below applies the appropriate transform to a 4-vector
// void Scene::matransform(stack<glm::mat4> &transfstack, float* values)
// {
//   mat4 transform = transfstack.top();
//   vec4 valvec = vec4(values[0],values[1],values[2],values[3]);
//   vec4 newval = transform * valvec;
//   for (int i = 0; i < 4; i++) values[i] = newval[i];
// }

void Scene::rightmultiply(const glm::mat4 &M, stack<Matrix> &transfstack)
{
  Matrix &T = transfstack.top();
  T.mat = T.mat * M;
  // cout << "after rightmultiply \n";
  // transfstack.top().print();
}

// help function much like the one from HW2
bool Scene::readvals (stringstream &s, const int numvals, float values[])
{
    for (int i = 0; i < numvals; i++)
    {
        s >> values[i];
        if (s.fail())
        {
            cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

// load file function
void Scene::loadFromFile(const char* filename)
{
    string str, cmd;
    ifstream in;
    in.open(filename);
    if (in.is_open())
    {
        stack <Matrix> transfstack;
        transfstack.push(Matrix());  // identity
        getline (in, str);
        while (in)
        {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#'))
            {
                // Ruled out comment and blank lines
                stringstream s(str);
                s >> cmd;
                int i;
                float values[10]; // Position and color for light, colors for others
                // Up to 10 params for cameras.
                bool validinput; // Validity of input

                // since I copied the skeleton from HW2, and there is no light command,
                // I deleted the cmd parser for light for now, this comment acts as the
                // placeholder incase if I need to implement light back later.

                // size command
                if (cmd == "size")
                {
                    validinput = readvals(s,2,values);
                    if (validinput)
                    {

                        //width = (int) values[0]; height = (int) values[1];
                        width = values[0]; height = values[1];
                    }
                }

                if (cmd == "maxdepth")
                {
                    validinput = readvals(s,1,values);
                    if (validinput)
                    {
                        maxdepth = values[0];
                    }
                }

                // camera command
                else if (cmd == "camera")
                {
                    validinput = readvals(s,10,values); // 10 values eye cen up fov
                    if (validinput)
                    {
                        lookFrom = new Point(values[0], values[1], values[2]);
                        cout << "printing Point lookFrom\n";
                        lookFrom->print();
                        lookAt = new Point(values[3], values[4], values[5]);
                        cout << "printing Point lookAt\n";
                        lookAt->print();

                        up = new Vector(values[6], values[7], values[8]);
                        // up->normalize();

                        cout << "printing Vector up\n";

                        fov = values[9];
                        cout << "printing fov value\n";
                        cout << fov << endl;
                        // declare Sampler object for later sample calculations
                        sampler = new Sampler(width, height);
                        cout << "printing Sampler width and height\n";
                        sampler->print();

                        film = new Film(width, height);

                        // here we pass a sample to fill the ray
                        camera = new Camera(*lookFrom, *lookAt, *up, fov, width, height);
                    }
                }
                // Material Commands
                // Ambient, diffuse, specular, shininess properties for each object.
                // Filling this in is pretty straightforward, so I've left it in
                // the skeleton, also as a hint of how to do the more complex ones.
                // Note that no transforms/stacks are applied to the colors.

                // ambient command
                else if (cmd == "ambient")
                {
                    validinput = readvals(s,3,values);
                    if (validinput)
                    {
                        ka = Color(values[0],values[1],values[2]);
                        cout << "ambient: ";
                        ka.print();
                    }
                }
                // diffuse command
                else if (cmd == "diffuse")
                {
                    validinput = readvals(s,3,values);
                    if (validinput)
                    {
                        kd = Color(values[0],values[1],values[2]);
                        cout << "diffuse: ";
                        kd.print();
                    }
                }
                // specular command
                else if (cmd == "specular")
                {
                    validinput = readvals(s,3,values);
                    if (validinput)
                    {
                        ks = Color(values[0],values[1],values[2]);
                        cout << "specular: ";
                        ks.print();
                    }
                }
                else if (cmd == "shininess")
                {
                    validinput = readvals(s,1,values);
                    if (validinput)
                    {
                        ksh = (float) values[0];
                        cout << "shininess: ";
                        cout << ksh << endl;
                    }
                }
                else if (cmd == "emission")
                {
                    validinput = readvals(s,3,values);
                    if (validinput)
                    {
                        ke = Color(values[0],values[1],values[2]);
                        cout << "emission: ";
                        ke.print();
                    }
                }

                // The followings are light related Commands
                // Directional Light
                else if (cmd == "directional") {
                    validinput = readvals(s,6,values);
                    if (validinput)
                    {
                        DirectionalLight* dl = new DirectionalLight(values[0], values[1], values[2], values[3], values[4], values[5]);
                        lights.push_back(dl);
                        std::cout << "push back lights" << '\n';
                        std::cout << lights.size() << '\n';

                        Vector dir_light_pos = Vector(values[0],values[1],values[2]);
                        cout << "directional light direction: ";
                        dir_light_pos.print();

                        Color dir_light_color = Color(values[3],values[4],values[5]);
                        cout << "directional light color: ";
                        dir_light_color.print();

                    }
                }

                // Point Light
                else if (cmd == "point") {
                    validinput = readvals(s,6,values);
                    if (validinput)
                    {
                        PointLight* pl = new PointLight(values[0], values[1], values[2], values[3], values[4], values[5]);
                        lights.push_back(pl);
                        std::cout << "push back lights" << '\n';
                        std::cout << lights.size() << '\n';

                        Point point_light_pos = Point(values[0],values[1],values[2]);
                        cout << "point light direction: ";
                        point_light_pos.print();

                        Color point_light_color = Color(values[3],values[4],values[5]);
                        cout << "point light color: ";
                        point_light_color.print();
                    }
                }

                // Attenuation factors
                else if (cmd == "attenuation") {
                    validinput = readvals(s,3,values);
                    if (validinput)
                    {
                        attenu_const = (float)values[0];
                        cout << "attenuation-const: ";
                        std::cout << attenu_const << '\n';

                        attenu_linear = (float)values[1];
                        cout << "attenuation-linear: ";
                        std::cout << attenu_linear << '\n';

                        attenu_quadra = (float)values[2];
                        cout << "attenuation-quadratic: ";
                        std::cout << attenu_quadra << '\n';
                    }
                }

                else if (cmd == "maxverts")
                {
                    validinput = readvals(s,1,values);
                    if (validinput)
                        maxverts = (int)values[0];
                    cout << "maxverts: " << maxverts << endl;

                }
                // vertex command
                else if (cmd == "vertex")
                {
                    if (vertex.size() >= maxverts)
                      // More vertices read than maxverts
                      cerr << "Reached Maximum Number of vertex " << maxverts << " Will ignore further vertices\n";
                    else
                    {
                        validinput = readvals(s,3,values);
                        if (validinput)
                        {
                            vertex.push_back(Vertex(values[0], values[1], values[2]));
                        }
                        //vertInd ++;
                    }
                }
                else if (cmd == "tri")
                {
                    validinput = readvals(s,3,values);
                    if (validinput)
                    {
                        tri.push_back(Tri(values[0], values[1], values[2]));

                        Triangle* t = new Triangle(vertex[int(values[0])].x, vertex[int(values[0])].y, vertex[int(values[0])].z,
                                                 vertex[int(values[1])].x, vertex[int(values[1])].y, vertex[int(values[1])].z,
                                                 vertex[int(values[2])].x, vertex[int(values[2])].y, vertex[int(values[2])].z, ka);
                        Shape* s = t;
                        BRDF brdf = BRDF(kd, ks, ka, ksh, ke);

                        ka.print();
                        Material* m = new Material(brdf);
                        // cout << "Color after material\n";
                        // m->getBRDF().ka.print();
                        if (transfstack.size() > 0)
                        {
                            // transfstack not empty
                            (*t).transform = transfstack.top();
                        }
                        Transformation objW = Transformation(transfstack.top());
                        // cout << "transfstack.top: \n";
                        // transfstack.top().print();
                        Transformation wObj = Transformation(transfstack.top().inverse());
                        // cout << "transfstack.top.inverse(): \n";
                        // transfstack.top().inverse().print();
                        GeometricPrimitive* gp = new GeometricPrimitive(objW, wObj, s, m);
                        primitives.push_back(gp);
                    }
                    //triNum ++;
                }
                else if (cmd == "sphere")
                {
                    validinput = readvals(s,4,values);
                    if (validinput)
                    {
                        sph.push_back(Sph(values[0], values[1], values[2], values[3]));
                        Sphere* sphere = new Sphere(values[0], values[1], values[2], values[3], ka);
                        Shape* s = sphere;
                        BRDF brdf = BRDF(kd, ks, ka, ksh, ke);
                        Material* m = new Material(brdf);
                        if (transfstack.size() > 0)
                        {
                            // transfstack not empty
                            (*sphere).transform = transfstack.top();
                        }
                        Transformation objW = Transformation(transfstack.top());
                        Transformation wObj = Transformation(transfstack.top().inverse());
                        GeometricPrimitive* gp = new GeometricPrimitive(objW, wObj, s, m);
                        primitives.push_back(gp);
                    }
                    //triNum ++;
                }
                else if (cmd == "pushTransform")
                {
                  transfstack.push(transfstack.top());
                }
                else if (cmd == "popTransform")
                {
                  if (transfstack.size() <= 1)
                  {
                    cerr << "Stack has no elements.  Cannot Pop\n";
                  }
                  else
                  {
                    transfstack.pop();
                  }
                }
                else if (cmd == "scale")
                {
                    validinput = readvals(s,3,values);
                    if (validinput)
                    {
                        Matrix m = Matrix();
                        // cout << "b4 scaling\n";
                        // m.print();
                        // cout << "Scaling:\n x: " << values[0] << " y: " << values[1] << " z: " << values[2] << endl;
                        m.scale(values[0], values[1], values[2]);
                        // cout << "after scaling\n";
                        // m.print();
                        rightmultiply(m.mat, transfstack);
                    }
                }
                else if (cmd == "translate")
                {
                    validinput = readvals(s,3,values);
                    if (validinput)
                    {
                        Matrix m = Matrix();
                        // cout << "b4 translating\n";
                        // m.print();
                        // cout << "Translating:\n x: " << values[0] << " y: " << values[1] << " z: " << values[2] << endl;
                        m.translate(values[0], values[1], values[2]);
                        // cout << "after translating\n";
                        // m.print();
                        rightmultiply(m.mat, transfstack);
                    }
                }
                else if (cmd == "rotate")
                {
                    validinput = readvals(s,4,values);
                    if (validinput)
                    {
                        Matrix m = Matrix();
                        // cout << "b4 rotating\n";
                        // m.print();
                        // cout << "Rotating:\n x: " << values[0] << " y: " << values[1] << " z: " << values[2] << endl;
                        m.rotate(values[0], values[1], values[2], values[3]);
                        // cout << "after rotating\n";
                        // m.print();
                        rightmultiply(m.mat, transfstack);
                    }
                }
                else if (cmd == "output")
                {
                    s >> cmd;
                    output = cmd;
                    cout << "output file: " << output << endl;
                }
                else
                {
                    cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline (in, str);
        }
    }
}

// main render function
void Scene::render()
{
    // check vertices
    // cout << "Printing all vertices:\n";
    // for (int i = 0; i < vertex.size(); i ++)
    //     vertex[i].print();
    // // check tri
    // cout << "Printing all tris\n";
    // for (int i = 0; i < tri.size(); i ++)
    //     tri[i].print();
    // // check spheres
    // cout << "Printing all spheres\n";
    // for (int i = 0; i < sph.size(); i ++)
    //     sph[i].print();

    // check triangles
    // cout << "Print all triangles and spheres\n";
    // for (int i = 0; i < shape.size(); i ++)
    //     shape[i]->print();
    // int count = 0;
    while (sampler->getSample(&sample))
    {
        camera->generateRay(sample, &ray);
        // cout << "Ray:\n";
        // ray.print();
        color = Color(0.0f, 0.0f, 0.0f);
        raytracer.trace(ray, 0, maxdepth, &color, primitives, lights, attenu_const, attenu_linear, attenu_quadra);
        // color.print();
        // if (color.r != 0.0f && color.g != 0.0f && color.b != 0.0f)
        //     count ++;
        film->commit(sample, color);
    }
    // cout << "Total intersected: " << count << endl;

    film->writeImage(output);
    cout << "There are total of " << primitives.size() << " objects\n";
}
