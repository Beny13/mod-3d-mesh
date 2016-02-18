#include "multisphere.h"

MultiSphere::MultiSphere()
{
}

MultiSphere::MultiSphere(int nb, double radius, int deplacementX, int deplacementY, Point3D origin)
    : nbSphere(nb), deplacementX(deplacementX), deplacementY(deplacementY), radius(radius), origin(origin)
{
    Sphere3D originalSphere(origin, radius);
    spheres.push_back(originalSphere);
    for(int i = 1; i < nbSphere; ++i){
        Point3D currentCenter(spheres.last().getOrigin().getX()+deplacementX, spheres.last().getOrigin().getY()+deplacementY, origin.getZ());
        spheres.push_back(Sphere3D(currentCenter, radius));
    }
}

double MultiSphere::getRelativeDistance(const Point3D &point) const
{
    double min = std::min(spheres.at(0).getRelativeDistance(point), spheres.at(1).getRelativeDistance(point));
    for (int i = 1; i < spheres.size()-1; ++i) {
        double currentMin = std::min(spheres.at(i).getRelativeDistance(point), spheres.at(i+1).getRelativeDistance(point));
        if(currentMin < min){
            min = currentMin;
        }
    }
    return min;
}
int MultiSphere::getNbSphere() const
{
    return nbSphere;
}

void MultiSphere::setNbSphere(int value)
{
    nbSphere = value;
}


