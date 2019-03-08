#include "Sampler.h"

using namespace std;

// default constructor
Sampler::Sampler()
{
    // empty for now
}
// constructor
Sampler::Sampler(int w, int h)
{
    width = w;
    height = h;
    currentX = currentY = 0;
}
bool Sampler::getSample(Sample* sample)
{
    // problematic implementation, fix later
    // if (currentX > width && currentY > height)
    //     return false;
    // if (currentX > width && currentY <= height)
    // {
    //     // reset x
    //     currentX = 0;
    //     currentY ++;
    // }
    // if (currentY > height && currentX <= width)
    // {
    //     // reset y
    //     currentY = 0;
    //     currentX ++;
    // }
    // sample = new Sample(currentX, currentY);
    // return true;
    if (currentX > width - 1)
        return false;
    sample = new Sample(currentX, currentY);
    if (currentY + 1 > height - 1) {
        currentY = 0;
        currentX++;
    } else {
        currentY++;
    }
    return true;
}

void Sampler::print()
{
    cout << "width: " << width << " height: " << height << endl;
    cout << "currentX: " << currentX << " currentY: " << currentY << endl;
}
