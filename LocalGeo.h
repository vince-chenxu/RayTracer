#ifndef LOCALGEO_H
#define LOCALGEO_H
using namespace std;

class LocalGeo
{
public:
    // Store the local geometry at the intersection point. May need to store
    // other quantities (eg. texture coordinate) in a more complicated
    // raytracer.

    // default constructor
    LocalGeo();
    // constructor
    LocalGeo(Point p, Normal n);
    ~LocalGeo();
private:
    Point pos
    Normal normal
};


#endif // LOCALGEO_H
