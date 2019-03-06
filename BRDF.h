using namespace std;

class BRDF
{
public:
    // default contructor
    BRDF();
    // contructor
    BRDF(Color kd_v, Color ks_v, Color ka_v, Color kr_v);
    // member variables
    // Storing information enough for shading
    // (it is not the actual BRDF function
    // in the rendering equation that will be covered later in the semester)
    Color kd, ks, ka, kr;
};
