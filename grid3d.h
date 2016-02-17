#ifndef GRID3D_H
#define GRID3D_H

#include "point3d.h"
#include "hexaedra.h"
#include "sphere3d.h"

class Grid3D
{
public:
    Grid3D();

    Grid3D(double xo, double yo, double zo, int nx, int ny, int nz);

    Point3D getOrigin() const;
    void setOrigin(const Point3D &value);

    void writeToFile(const QString & path);
    void writeToFile(const QString & path, const Sphere3D & sphere);

    int getNx() const;
    void setNx(int value);

    int getNy() const;
    void setNy(int value);

    int getNz() const;
    void setNz(int value);

    QVector<QVector<QVector<double> > > getProperties() const;
    void setProperties(const QVector<QVector<QVector<double> > > &value);

    double getProperty(int x, int y, int z);
    void setProperty(int x, int y, int z, double value);

    void setPropertiesFromSphere(const Sphere3D & sphere);

private:
    Point3D getCoordinatesFromIndex(int x, int y, int z);

    Point3D origin;
    int nx, ny, nz;
    QVector < QVector < QVector < double > > > properties;
};

#endif // GRID3D_H
