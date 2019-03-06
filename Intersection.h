using namespace std;

class Intersection
{
public:
    // default constructor
    Intersection();
    // constructor
    Intersection(LocalGeo geo, Primitive* prim);
    // destructor
    ~Intersection();

private:
    // member varaible
    LocalGeo localGeo
    Primitive* primitive
};
