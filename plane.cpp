#include "plane.h"

Plane::Plane(Point3D origin)
    : origin(origin) {

}

double Plane::getRelativeDistance(const Point3D &point) const
{
    return point.getZ() - origin.getZ();
}
