#include "sphere3d.h"

Sphere3D::Sphere3D()
{}

Sphere3D::Sphere3D(Point3D origin, double radius)
 : origin(origin), radius(radius) {}

Point3D Sphere3D::getOrigin() const
{
    return origin;
}

void Sphere3D::setOrigin(const Point3D &value)
{
    origin = value;
}
double Sphere3D::getRadius() const
{
    return radius;
}

void Sphere3D::setRadius(double value)
{
    radius = value;
}

double Sphere3D::getRelativeDistance(const Point3D &point) const
{
    return sqrt(pow(point.getX() - origin.getX(), 2)
                + pow(point.getY() - origin.getY(), 2)
                + pow(point.getZ() - origin.getZ(), 2)) - radius;
}

bool Sphere3D::contains(const Point3D &point) const
{
    return getRelativeDistance(point) < 0;
}


