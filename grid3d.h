#ifndef GRID3D_H
#define GRID3D_H

#include "point3d.h"
#include "hexaedra.h"

class Grid3D
{
public:
    Grid3D();

    Grid3D(double xo, double yo, double zo, int nx, int ny, int nz);

    Point3D getOrigin() const;
    void setOrigin(const Point3D &value);

    void writeToFile(const QString & path);

    int getNx() const;
    void setNx(int value);

    int getNy() const;
    void setNy(int value);

    int getNz() const;
    void setNz(int value);

private:
    Point3D origin;
    int nx, ny, nz;
};

#endif // GRID3D_H
