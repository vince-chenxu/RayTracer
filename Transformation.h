using namespace std;

class Transformation
{
    // Support Point, Vector, Normal, Ray, LocalGeo transformation by
    // operator * overloading
public:
    // default constructor
    Transformation();

private:
    Point* p;
    Vector* v;
    Normal* n;
    Ray* r;
    LocalGeo* lg;
};
