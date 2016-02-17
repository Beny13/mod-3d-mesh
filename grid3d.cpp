#include "grid3d.h"
Grid3D::Grid3D(){}

Grid3D::Grid3D(double xo, double yo, double zo, int nx, int ny, int nz)
 : origin(Point3D(xo, yo,zo)), nx(nx), ny(ny), nz(nz){
}

Point3D Grid3D::getOrigin() const
{
    return origin;
}

void Grid3D::setOrigin(const Point3D &value)
{
    origin = value;
}

void Grid3D::writeToFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream stream(&file);
    stream  << "MeshVersionFormatted 1" << endl
            << "Dimension" << endl
            << "3" << endl;

    stream  << "Vertices" << endl
            <<  nx * ny * nz << endl;
    QVector<Hexaedra> hexs;

    int xD = 1;
    int yD = nx;
    int zD = nx * ny;
    for (int z = 0; z < nz; ++z) {
        for (int y = 0; y < ny; ++y) {
            for (int x = 0; x < nx; ++x) {
                stream << " " << origin.getX() + x
                       << " " << origin.getY() + y
                       << " " << origin.getZ() + z
                       << " 0" << endl;

                if (!(x == nx - 1 || y == ny - 1 || z == nz - 1)) {
                    hexs.push_back(Hexaedra(
                        (x + 0) + yD * (y + 0) + zD * (z + 0),
                        (x + 1) + yD * (y + 0) + zD * (z + 0),
                        (x + 1) + yD * (y + 1) + zD * (z + 0),
                        (x + 0) + yD * (y + 1) + zD * (z + 0),
                        (x + 0) + yD * (y + 0) + zD * (z + 1),
                        (x + 1) + yD * (y + 0) + zD * (z + 1),
                        (x + 1) + yD * (y + 1) + zD * (z + 1),
                        (x + 0) + yD * (y + 1) + zD * (z + 1)
                    ));
                }
            }
        }
    }

    stream  << "Hexahedra" << endl
            << hexs.size() << endl;

    for (int i = 0; i < hexs.size(); ++i) {
        stream << hexs.at(i).format() << endl;
    }

    stream << "End" << endl;
}
int Grid3D::getNx() const
{
    return nx;
}

void Grid3D::setNx(int value)
{
    nx = value;
}
int Grid3D::getNy() const
{
    return ny;
}

void Grid3D::setNy(int value)
{
    ny = value;
}
int Grid3D::getNz() const
{
    return nz;
}

void Grid3D::setNz(int value)
{
    nz = value;
}







