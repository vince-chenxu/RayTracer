using namespace std;

class Intersection
{
public:
    // default constructor
    Intersection();
    // constructor
    // Intersection(LocalGeo geo, Primitive* prim);
    Intersection(LocalGeo geo, Shape* s);
    // destructor
    ~Intersection();

private:
    // member varaible
    LocalGeo localGeo
    // Primitive* primitive
    Shape* shape;
};
