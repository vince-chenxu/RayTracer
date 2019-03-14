// header files
#include "Scene.h"

using namespace std;

Scene::Scene()
{
    // default constructor empty for now
}

Scene::Scene(const char* filename)
{
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

void Scene::rightmultiply(const glm::mat4 & M, stack<Matrix> &transfstack)
{
  Matrix &T = transfstack.top();
  T.mat = T.mat * M;
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
                // cout << cmd << endl;
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

                // camera command
                else if (cmd == "camera")
                {
                    validinput = readvals(s,10,values); // 10 values eye cen up fov
                    if (validinput)
                    {
                        // // lookFrom
                        // //vec3 from = vec3(values[0],values[1],values[2]);
                        lookFrom = new Point(values[0], values[1], values[2]);
                        cout << "printing Point lookFrom\n";
                        lookFrom->print();
                        // // lookAt
                        // //vec3 at = vec3(values[3],values[4],values[5]);
                        lookAt = new Point(values[3], values[4], values[5]);
                        cout << "printing Point lookAt\n";
                        lookAt->print();
                        //center = at;
                        //eyeinit = from;
                        // Calculate the direction of eye
                        //vec3 eyeDirection = at - from;
                        // Normalize the vector
                        //upinit = glm::normalize(vec3(values[6], values[7], values[8]));
                        // Transform the vector by calling upvector function
                        //upinit = Transform::upvector(upinit,eyeDirection);
                        // up
                        up = new Vector(values[6], values[7], values[8]);
                        up->normalize();
                        // Vector temp1 = *lookFrom - *lookAt;
                        // *up = up->cross(*up, temp1);
                        // Vector temp2 = up->cross(*up, temp1);
                        // *up = up->cross(temp2, temp1) * -1;
                        // up->normalize();
                        cout << "printing Vector up\n";
                        // up->print();
                        // Set fovy value
                        fov = values[9];
                        cout << "printing fov value\n";
                        cout << fov << endl;
                        // declare Sampler object for later sample calculations
                        sampler = new Sampler(width, height);
                        cout << "printing Sampler width and height\n";
                        sampler->print();
                        // below is a place holder
                        //sample = new Sample();

                        // Color object
                        //color = new Color();

                        // Ray object
                        //ray = new Ray();

                        // Film object
                        film = new Film(width, height);

                        // here we pass a sample to fill the ray
                        camera = new Camera(*lookFrom, *lookAt, *up, fov, width, height);
                        // here we get a ray back

                        // now we trace the ray with raytracer
                        //RayTracer rayTracer();
                        // now we get the color

                    }
                }

                // ambient command
                else if (cmd == "ambient")
                {
                    validinput = readvals(s,3,values); // 10 values eye cen up fov
                    if (validinput)
                    {
                        // values[0] = R, values[1] = G, values[2] = B
                        ka = Color(values[0],values[1],values[2]);
                        cout << "ambient: ";
                        ka.print();
                        // cout << "about to seg fault\n";
                        // if (shape.size() > 0)
                        // shape[shape.size()]->color = new Color(values[0],values[1],values[2]);
                        // else
                            // shape[0]->color = *ka;
                    }
                }
                // diffuse command
                else if (cmd == "diffuse")
                {
                    validinput = readvals(s,3,values); // 10 values eye cen up fov
                    if (validinput)
                    {
                        // values[0] = R, values[1] = G, values[2] = B
                        kd = Color(values[0],values[1],values[2]);
                        cout << "diffuse: ";
                        kd.print();
                    }
                }
                // specular command
                else if (cmd == "specular")
                {
                    validinput = readvals(s,3,values); // 10 values eye cen up fov
                    if (validinput)
                    {
                        // values[0] = R, values[1] = G, values[2] = B
                        ks = Color(values[0],values[1],values[2]);
                        cout << "specular: ";
                        ks.print();
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
                            // for (int i  = 0; i < 3; i ++)
                            // {
                            //     if (value[i][0] == '+')
                            //         vertArray[vertInd][i] = int(values[i][1]-'0');
                            //     else
                            //         vertArray[vertInd][i] = stoi(values[i]);
                            // }
                            // vertArray[vertInd][0] = values[0]; // x
                            // vertArray[vertInd][1] = values[1]; // y
                            // vertArray[vertInd][2] = values[2]; // z
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
                        // triVec.push(values[0]); // coord 1
                        // triVec.push(values[1]); // coord 2
                        // triVec.push(values[2]); // coord 3
                        tri.push_back(Tri(values[0], values[1], values[2]));
                        // shape.push_back(new Triangle(vertex[int(values[0])].x, vertex[int(values[0])].y, vertex[int(values[0])].z,
                                                 // vertex[int(values[1])].x, vertex[int(values[1])].y, vertex[int(values[1])].z,
                                                 // vertex[int(values[2])].x, vertex[int(values[2])].y, vertex[int(values[2])].z, *ka));
                        Triangle* t = new Triangle(vertex[int(values[0])].x, vertex[int(values[0])].y, vertex[int(values[0])].z,
                                                 vertex[int(values[1])].x, vertex[int(values[1])].y, vertex[int(values[1])].z,
                                                 vertex[int(values[2])].x, vertex[int(values[2])].y, vertex[int(values[2])].z, ka);
                        Shape* s = t;
                        // BRDF constructor needs kr and ke, modify later, use ka as kr placeholder
                        // cout << "b4 brdf\n";
                        BRDF brdf = BRDF(kd, ks, ka);
                        // cout << "after brdf\n";
                        // cout << "Color b4 going into material\n";
                        ka.print();
                        Material* m = new Material(brdf);
                        // cout << "Color after material\n";
                        // m->getBRDF().ka.print();
                        if (transfstack.size() > 0)
                        {
                            // transfstack not empty
                            (*t).transform = transfstack.top();
                        }
                        Transformation* objW = new Transformation(transfstack.top());
                        Transformation* wObj = new Transformation(transfstack.top().inverse());
                        GeometricPrimitive* gp = new GeometricPrimitive(*objW, *wObj, s, m);
                        primitives.push_back(gp);
                    }
                    //triNum ++;
                }
                else if (cmd == "sphere")
                {
                    validinput = readvals(s,4,values);
                    if (validinput)
                    {
                        // triVec.push(values[0]); // coord 1
                        // triVec.push(values[1]); // coord 2
                        // triVec.push(values[2]); // coord 3
                        sph.push_back(Sph(values[0], values[1], values[2], values[3]));
                        // shape.push_back(new Sphere(values[0], values[1], values[2], values[3], *ka));
                        Sphere* sphere = new Sphere(values[0], values[1], values[2], values[3], ka);
                        Shape* s = sphere;
                        BRDF brdf = BRDF(kd, ks, ka);
                        Material* m = new Material(brdf);
                        if (transfstack.size() > 0)
                        {
                            // transfstack not empty
                            (*sphere).transform = transfstack.top();
                        }
                        Transformation* objW = new Transformation(transfstack.top());
                        Transformation* wObj = new Transformation(transfstack.top().inverse());
                        GeometricPrimitive* gp = new GeometricPrimitive(*objW, *wObj, s, m);
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
                        cout << "b4 scaling\n";
                        m.print();
                        cout << "Scaling:\n x: " << values[0] << " y: " << values[1] << " z: " << values[2] << endl;
                        m.scale(values[0], values[1], values[2]);
                        cout << "after scaling\n";
                        m.print();
                        rightmultiply(m.mat, transfstack);
                    }
                }
                else if (cmd == "translate")
                {
                    validinput = readvals(s,3,values);
                    if (validinput)
                    {
                        Matrix m = Matrix();
                        cout << "b4 translating\n";
                        m.print();
                        cout << "Translating:\n x: " << values[0] << " y: " << values[1] << " z: " << values[2] << endl;
                        m.translate(values[0], values[1], values[2]);
                        cout << "after translating\n";
                        m.print();
                        rightmultiply(m.mat, transfstack);
                    }
                }
                else if (cmd == "rotate")
                {
                    validinput = readvals(s,4,values);
                    if (validinput)
                    {
                        Matrix m = Matrix();
                        cout << "b4 rotating\n";
                        m.print();
                        cout << "Rotating:\n x: " << values[0] << " y: " << values[1] << " z: " << values[2] << endl;
                        m.rotate(values[0], values[1], values[2], values[3]);
                        cout << "after rotating\n";
                        m.print();
                        rightmultiply(m.mat, transfstack);
                    }
                }
                // Material Commands
                // Ambient, diffuse, specular, shininess properties for each object.
                // Filling this in is pretty straightforward, so I've left it in
                // the skeleton, also as a hint of how to do the more complex ones.
                // Note that no transforms/stacks are applied to the colors.

          // else if (cmd == "ambient") {
          //   validinput = readvals(s, 3, values); // colors
          //   if (validinput) {
          //     for (i = 0; i < 3; i++) {
          //       ambient[i] = values[i];
          //     }
          //   }
          // } else if (cmd == "diffuse") {
          //   validinput = readvals(s, 3, values);
          //   if (validinput) {
          //     for (i = 0; i < 3; i++) {
          //       diffuse[i] = values[i];
          //     }
          //   }
          // } else if (cmd == "specular") {
          //   validinput = readvals(s, 3, values);
          //   if (validinput) {
          //     for (i = 0; i < 3; i++) {
          //       specular[i] = values[i];
          //     }
          //   }
          // }
          //   // Not applicable yet
          //   else if (cmd == "emission") {
          //   validinput = readvals(s, 4, values);
          //   if (validinput) {
          //     for (i = 0; i < 4; i++) {
          //       emission[i] = values[i];
          //     }
          //   }
          // }
          //   // Not applicable yet
          //   else if (cmd == "shininess") {
          //   validinput = readvals(s, 1, values);
          //   if (validinput) {
          //     shininess = values[0];
          //   }
          // } else if (cmd == "size") {
          //   validinput = readvals(s,2,values);
          //   if (validinput) {
          //     w = (int) values[0]; h = (int) values[1];
          //   }
          // } else if (cmd == "camera") {
          //   validinput = readvals(s,10,values); // 10 values eye cen up fov
          //   if (validinput) {
          //
          //     // YOUR CODE FOR HW 2 HERE
          //     // Use all of values[0...9]
          //     // You may need to use the upvector fn in Transform.cpp
          //     // to set up correctly.
          //     // Set eyeinit upinit center fovy in variables.h
          //
          //     // The lookFrom vector
          //     vec3 from = vec3(values[0],values[1],values[2]);
          //     // The lookAt vector
          //     vec3 at = vec3(values[3],values[4],values[5]);
          //     center = at;
          //     eyeinit = from;
          //     // Calculate the direction of eye
          //     vec3 eyeDirection = at - from;
          //     // Normalize the vector
          //     upinit = glm::normalize(vec3(values[6], values[7], values[8]));
          //     // Transform the vector by calling upvector function
          //     upinit = Transform::upvector(upinit,eyeDirection);
          //     // Set fovy value
          //     fovy = values[9];
          //
          //   }
          // }
          //
          // // I've left the code for loading objects in the skeleton, so
          // // you can get a sense of how this works.
          // // Also look at demo.txt to get a sense of why things are done this way.
          // else if (cmd == "sphere" || cmd == "cube" || cmd == "teapot") {
          //   if (numobjects == maxobjects) { // No more objects
          //     cerr << "Reached Maximum Number of Objects " << numobjects << " Will ignore further objects\n";
          //   } else {
          //     validinput = readvals(s, 1, values);
          //     if (validinput) {
          //       object * obj = &(objects[numobjects]);
          //       obj->size = values[0];
          //
          //       // Set the object's light properties
          //       for (i = 0; i < 4; i++) {
          //         (obj->ambient)[i] = ambient[i];
          //         (obj->diffuse)[i] = diffuse[i];
          //         (obj->specular)[i] = specular[i];
          //         (obj->emission)[i] = emission[i];
          //       }
          //       obj->shininess = shininess;
          //
          //       // Set the object's transform
          //       obj->transform = transfstack.top();
          //
          //       // Set the object's type
          //       if (cmd == "sphere") {
          //         obj->type = sphere;
          //       } else if (cmd == "cube") {
          //         obj->type = cube;
          //       } else if (cmd == "teapot") {
          //         obj->type = teapot;
          //       }
          //     }
          //     ++numobjects;
          //   }
          // }
          //
          // else if (cmd == "translate") {
          //   validinput = readvals(s,3,values);
          //   if (validinput) {
          //
          //     // YOUR CODE FOR HW 2 HERE.
          //     // Think about how the transformation stack is affected
          //     // You might want to use helper functions on top of file.
          //     // Also keep in mind what order your matrix is!
          //
          //     // Translate the matrix
          //     mat4 matrixTranslation =  Transform::translate(values[0], values[1], values[2]);
          //     // Call helper function
          //     rightmultiply(matrixTranslation, transfstack);
          //
          //   }
          // }
          // else if (cmd == "scale") {
          //   validinput = readvals(s,3,values);
          //   if (validinput) {
          //
          //     // YOUR CODE FOR HW 2 HERE.
          //     // Think about how the transformation stack is affected
          //     // You might want to use helper functions on top of file.
          //     // Also keep in mind what order your matrix is!
          //
          //     // Scale the matrix
          //     mat4 matrixScaling = Transform::scale(values[0], values[1], values[2]);
          //     // Call helper function
          //     rightmultiply(matrixScaling, transfstack);
          //
          //   }
          // }
          // else if (cmd == "rotate") {
          //   validinput = readvals(s,4,values);
          //   if (validinput) {
          //
          //     // YOUR CODE FOR HW 2 HERE.
          //     // values[0..2] are the axis, values[3] is the angle.
          //     // You may want to normalize the axis (or in Transform::rotate)
          //     // See how the stack is affected, as above.
          //     // Note that rotate returns a mat3.
          //     // Also keep in mind what order your matrix is!
          //
          //     // Create temp vector used for rotatio
          //     vec3 temp = vec3(values[0], values[1], values[2]);
          //     // Rotate the matrix by calling rotate
          //     mat4 matrixRotation = mat4(Transform::rotate(values[3], temp));
          //     // Call helper function
          //     rightmultiply(matrixRotation, transfstack);
          //
          //   }
          // }
          //
          // // I include the basic push/pop code for matrix stacks
          // else if (cmd == "pushTransform") {
          //   transfstack.push(transfstack.top());
          // } else if (cmd == "popTransform") {
          //   if (transfstack.size() <= 1) {
          //     cerr << "Stack has no elements.  Cannot Pop\n";
          //   } else {
          //     transfstack.pop();
          //   }
          // }
          // // maxverts command
          // else if (cmd == "maxverts")
          // {
          //     validinput = readvals(s,1,values);
          //     if (validinput)
          //         maxverts = (int)values[0];
          //
          // }
          // // vertex command
          // else if (cmd == "vertex")
          // {
          //     if (vertInd + 1 > maxverts)
          //       // More vertices read than maxverts
          //       cerr << "Reached Maximum Number of vertex " << maxverts << " Will ignore further vertices\n";
          //     else
          //     {
          //         validinput = readvals(s,3,values);
          //         if (validinput)
          //         {
          //             for (int i  = 0; i < 3; i ++)
          //             {
          //                 if (value[i][0] == '+')
          //                     vertArray[vertInd][i] = int(values[i][1]-'0');
          //                 else
          //                     vertArray[vertInd][i] = stoi(values[i]);
          //             }
          //             // vertArray[vertInd][0] = values[0]; // x
          //             // vertArray[vertInd][1] = values[1]; // y
          //             // vertArray[vertInd][2] = values[2]; // z
          //         }
          //         vertInd ++;
          //     }
          // }
          // else if (cmd == "tri")
          // {
          //     validinput = readvals(s,3,values);
          //     if (validinput)
          //     {
          //         triVec.push(values[0]); // coord 1
          //         triVec.push(values[1]); // coord 2
          //         triVec.push(values[2]); // coord 3
          //     }
          //     triNum ++;
          // }
          // else if (cmd == "sphere")
          // {
          //     validinput = readvals(s,4,values);
          //     if (validinput)
          //     {
          //         for (int i  = 0; i < 4; i ++)
          //         {
          //             if (value[i][0] == '+')
          //                 sphereVec[sphereInd][i] = 0.5;
          //             else
          //                 // assume this works for now
          //                 sphereVec[sphereInd][i] = stod(values[i]);
          //         }
          //     }
          //     triNum ++;
          // }
            else
            {
                cerr << "Unknown Command: " << cmd << " Skipping \n";
            }
        }
            getline (in, str);
      }

      // Set up initial position for eye, up and amount
      // As well as booleans

    //   eye = eyeinit;
    //   up = upinit;
    //   amount = amountinit;
    //   sx = sy = 1.0;  // keyboard controlled scales in x and y
    //   tx = ty = 0.0;  // keyboard controllled translation in x and y
    //   useGlu = false; // don't use the glu perspective/lookat fns
    //
    //   glEnable(GL_DEPTH_TEST);
    // } else {
    //   cerr << "Unable to Open Input Data File " << filename << "\n";
    //   throw 2;
    }
}

// main render function
void Scene::render()
{
    // check vertices
    cout << "Printing all vertices:\n";
    for (int i = 0; i < vertex.size(); i ++)
        vertex[i].print();
    // check tri
    cout << "Printing all tris\n";
    for (int i = 0; i < tri.size(); i ++)
        tri[i].print();
    // check spheres
    cout << "Printing all spheres\n";
    for (int i = 0; i < sph.size(); i ++)
        sph[i].print();

    // check triangles
    cout << "Print all triangles and spheres\n";
    for (int i = 0; i < shape.size(); i ++)
        shape[i]->print();
    while (sampler->getSample(&sample))
    {
        //cout << "Printing sample coords\n";
        //sample.print();
        //cout << "Printing sampler\n";
        //sampler->print();
        camera->generateRay(sample, &ray);
        //cout << "Ray: \n";
        //ray.print();
        raytracer.trace(ray, 0, &color, primitives);
        // color.print();
        film->commit(sample, color);
    }
    film->writeImage();
    cout << "There are total of " << primitives.size() << " objects\n";
}
