#ifndef POINT3D_H
#define POINT3D_H

#include <QtCore>

class Point3D
{
public:
    Point3D();
    Point3D(double x, double y, double z);

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getZ() const;
    void setZ(double value);

    Point3D translate(const Point3D & normal, double d) const;

private:
    double x;
    double y;
    double z;
};

QDebug operator<<(QDebug dbg, const Point3D & point);

#endif // POINT3D_H
