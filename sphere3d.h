#ifndef SPHERE3D_H
#define SPHERE3D_H

#include "point3d.h"

class Sphere3D
{
public:
    Sphere3D();
    Sphere3D(Point3D origin, double radius);

    Point3D getOrigin() const;
    void setOrigin(const Point3D &value);

    double getRadius() const;
    void setRadius(double value);

    double getRelativeDistance(const Point3D & point) const;

    bool contains(const Point3D &point) const;

private:
    Point3D origin;
    double radius;
};

#endif // SPHERE3D_H
