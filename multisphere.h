#ifndef MULTISPHERE_H
#define MULTISPHERE_H

#include "point3d.h"
#include "sphere3d.h"

#include <QtCore>

//La classe Multisphere permet de créer une multitude de spheres sur une trajectoire définie

class MultiSphere : public ImplicitObject
{
public:
    MultiSphere();
    MultiSphere(int nb, double radius, int deplacementX, int deplacementY, Point3D origin);
    double getRelativeDistance(const Point3D & point) const;
    int getNbSphere() const;
    void setNbSphere(int value);

private:
    int nbSphere;
    //déplacement d'une sphère à l'autre sur l'axe X
    int deplacementX;
    //déplacement d'une sphère à l'autre sur l'axe Y
    int deplacementY;
    //rayon d'une sphère
    double radius;
    QVector<Sphere3D> spheres;
    //point d'origine de la première sphère
    Point3D origin;
};


#endif // MULTISPHERE_H
