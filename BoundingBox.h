#include "BoundingBox.h"

using namespace std;

BoundingBox::BoundingBox()
{

}
BoundingBox::BoundingBox(const Point &min, const Point &max)
{
    min_pos = min;
    max_pos = max;
}
bool BoundingBox::intersectP(const Ray &ray)
{
    
}
