#ifndef IMPLICITOBJECT_H
#define IMPLICITOBJECT_H

#include "point3d.h"

class ImplicitObject
{
public:
    virtual double getRelativeDistance(const Point3D & point) const = 0;
};

#endif // IMPLICITOBJECT_H
