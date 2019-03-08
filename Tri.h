#ifndef TRI_H
#define TRI_H
#include <iostream>
using namespace std;

class Tri
{
public:
    Tri(int x_val, int y_val, int z_val);
    void print();
    // 3 indices of vertices that form a triangle
    int x, y, z;
};
#endif // TRI_H
