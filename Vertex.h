#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
using namespace std;

class Vertex
{
public:
    Vertex(int x_val, int y_val, int z_val);
    void print();
    int x, y, z;
};
#endif // VERTEX_H
