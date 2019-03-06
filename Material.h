using namespace std;

class Material
{
    // Class for storing material. For this example, it just returns a constant
    // material regardless of what local is. Later on, when we want to support
    // texture mapping, this need to be modified.
public:
    void getBRDF(LocalGeo& local, BRDF* brdf);
private:
    BRDF constantBRDF;   
};
