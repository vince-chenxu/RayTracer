using namespace std;

class Sampler
{
    // It will generate (x,y) of a screen sample and return true.
    // Next time it gets called, it will generate another sample for the next pixel.
    // It will return false when all the samples from all the pixels
    // are generated. (In our case, we generate 1 sample per pixel, at the pixel sample.
    // Later on, if we want to do multi-sample per pixel, we need to modify this class.

public:
    // default constructor
    Sampler();
    // constructor
    Sampler(int w, int h);
    bool getSample(Sample* sample);
    //bool getSample(float x, float y);
private:
    int width, height;
    // current pixel tracker (x,y), assume 1 sample per pixel
    int currentX, currentY;
};
