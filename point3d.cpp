#include "point3d.h"


Point3D::Point3D()
{
}

Point3D::Point3D(double x, double y, double z)
    : x(x), y(y), z(z)
{
}
double Point3D::getX() const
{
    return x;
}

void Point3D::setX(double value)
{
    x = value;
}
double Point3D::getY() const
{
    return y;
}

void Point3D::setY(double value)
{
    y = value;
}
double Point3D::getZ() const
{
    return z;
}

void Point3D::setZ(double value)
{
    z = value;
}

Point3D Point3D::translate(const Point3D &normal, double d) const
{
    return Point3D(getX() + d*normal.getX(),
                   getY() + d*normal.getY(),
                   getZ() + d*normal.getZ());
}

QDebug operator<<(QDebug dbg, const Point3D & point)
{
    dbg.nospace()
        << "Point3D(x: " << point.getX()
        << ", y: " << point.getY()
        << ", z: " << point.getZ()
        << ")"
    ;

    return dbg.space();
}


