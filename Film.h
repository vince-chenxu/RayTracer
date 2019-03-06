using namespace std;

class Film
{
    // Can be implemented just by a 2D array of Color (Later on, we can
    // implement more complicated things such as multi-sample per pixel, or
    // post processing, eg. tone mapping in this class)
public:
    // Will write the color to (sample.x, sample.y) on the image
    void commit(Sample& sample, Color& color);
    // Output image to a file
    void writeImage();
};
