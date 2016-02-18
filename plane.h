#ifndef PLANE_H
#define PLANE_H

#include "implicitobject.h"

class Plane : public ImplicitObject
{
public:
    Plane(Point3D origin);
    double getRelativeDistance(const Point3D & point) const;
private:
    Point3D origin;
};

#endif // PLANE_H
