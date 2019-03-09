#include "Film.h"

using namespace std;

// default constructor
Film::Film()
{
    // default pixel value 500x500
    width = height = 500;
    pix = width * height;
    pixels = new BYTE[3 * pix];
    FreeImage_Initialise();
    //img = FreeImage_Allocate(0, 0, 0);
}
// constructor
Film::Film(int w, int h)
{
    width = w;
    height = h;
    pix = width * height;
    pixels = new BYTE[3 * pix];
    FreeImage_Initialise();
    // 24 bits per pixel
    img = FreeImage_Allocate(width, height, 24);
}
// destructor
Film::~Film()
{
    // free memory allocation for pixels
    delete[] pixels;
}
void Film::commit(Sample& sample, Color color)
{
    // to prevent it goes out of bound
    //color.print();
    c.rgbRed = min((color.r * 255.0f), 255.0f);
    c.rgbGreen = min((color.g * 255.0f), 255.0f);
    c.rgbBlue = min((color.b * 255.0f), 255.0f);
    FreeImage_SetPixelColor(img, (unsigned int)sample.x, (unsigned int)sample.y, &c);
}

void Film::writeImage()
{
    //img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
    // add code here
    if (FreeImage_Save(FIF_PNG, img, "RayTracer.png", 0))
        cout << "image saved successfully\n";
    else
        cout << "image saved unsuccessfully\n";
    FreeImage_DeInitialise();
}
