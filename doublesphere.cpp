#include "doublesphere.h"

DoubleSphere::DoubleSphere(Sphere3D sphere1, Sphere3D sphere2)
 : sphere1(sphere1), sphere2(sphere2){
}

double DoubleSphere::getRelativeDistance(const Point3D &point) const
{
    return std::min(sphere1.getRelativeDistance(point), sphere2.getRelativeDistance(point));
}
