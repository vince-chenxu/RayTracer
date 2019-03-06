using namespace std;

class sampler
{
    // It will generate (x,y) of a screen sample and return true.
    // Next time it gets called, it will generate another sample for the next pixel.
    // It will return false when all the samples from all the pixels
    // are generated. (In our case, we generate 1 sample per pixel, at the pixel sample.
    // Later on, if we want to do multi-sample per pixel, we need to modify this class.

public:
    bool getSample(Sample* sample);
};
