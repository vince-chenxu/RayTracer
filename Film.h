#ifndef FILM_H
#define FILM_H
#include <iostream>
#include "Sample.h"
// #include "Sample.h"
#include "Color.h"
#include "include/FreeImage.h"
using namespace std;

class Film
{
    // Can be implemented just by a 2D array of Color (Later on, we can
    // implement more complicated things such as multi-sample per pixel, or
    // post processing, eg. tone mapping in this class)
public:
    // default constructor
    Film();
    // constructor
    Film(int w, int h);
    // destructor
    ~Film();
    // Will write the color to (sample.x, sample.y) on the image
    void commit(Sample& sample, Color color);
    // Output image to a file
    void writeImage();
private:
    // member variables
    int width, height, pix;
    BYTE* pixels;
    RGBQUAD c;
    FIBITMAP* img;
};


#endif // FILM_H
