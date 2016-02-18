#ifndef DOUBLESPHERE_H
#define DOUBLESPHERE_H

#include "implicitobject.h"
#include "sphere3d.h"

class DoubleSphere : public ImplicitObject
{
public:
    DoubleSphere(Sphere3D sphere1, Sphere3D sphere2);
    double getRelativeDistance(const Point3D & point) const;
private:
    Sphere3D sphere1;
    Sphere3D sphere2;
};

#endif // DOUBLESPHERE_H
