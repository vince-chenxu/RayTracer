#ifndef SAMPLE_H
#define SAMPLE_H
#include <iostream>
using namespace std;

class Sample
{
public:
    // default constructor
    Sample();
    // constructor
    Sample(float x_val, float y_val);
    void print();
    float x, y; // store member coords
};

#endif // SAMPLE_H
