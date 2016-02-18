#include "grid3d.h"
Grid3D::Grid3D(){}

Grid3D::Grid3D(double xo, double yo, double zo, int nx, int ny, int nz)
 : origin(Point3D(xo, yo,zo)), nx(nx), ny(ny), nz(nz) {
    properties.resize(nz);
    for (int i = 0; i < nz; ++i) {
        properties[i].resize(ny);
        for (int j = 0; j < ny; ++j) {
            properties[i][j].fill(0, nx);
        }
    }
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
                stream << Point3D(origin.getX() + x, origin.getY() + y, origin.getZ() + z).format()
                       << endl;

                if (!(x == nx - 1 || y == ny - 1 || z == nz - 1)) {
                    hexs.push_back(Hexaedra(
                        xD * (x + 0) + yD * (y + 0) + zD * (z + 0),
                        xD * (x + 1) + yD * (y + 0) + zD * (z + 0),
                        xD * (x + 1) + yD * (y + 1) + zD * (z + 0),
                        xD * (x + 0) + yD * (y + 1) + zD * (z + 0),
                        xD * (x + 0) + yD * (y + 0) + zD * (z + 1),
                        xD * (x + 1) + yD * (y + 0) + zD * (z + 1),
                        xD * (x + 1) + yD * (y + 1) + zD * (z + 1),
                        xD * (x + 0) + yD * (y + 1) + zD * (z + 1)
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

QVector<QVector<QVector<double> > > Grid3D::getProperties() const
{
    return properties;
}

void Grid3D::setProperties(const QVector<QVector<QVector<double> > > &value)
{
    properties = value;
}

double Grid3D::getProperty(int x, int y, int z) const
{
    return properties[z][y][x];
}

void Grid3D::setProperty(int x, int y, int z, double value)
{
    properties[z][y][x] = value;
}

void Grid3D::setShape(const ImplicitObject &object)
{
    for (int z = 0; z < nz; ++z) {
        for (int y = 0; y < ny; ++y) {
            for (int x = 0; x < nx; ++x) {
                setProperty(x,
                            y,
                            z,
                            object.getRelativeDistance(Point3D(x,y,z)));
            }
        }
    }
}

QVector<Point3D> Grid3D::getShapePoints() const
{
    QVector<Point3D> shapePoints;
    for (int z = 0; z < nz - 1; ++z) {
        for (int y = 0; y < ny - 1; ++y) {
            for (int x = 0; x < nx - 1; ++x) {
                Point3D reference = getCoordinatesFromIndex(x, y, z);
                Point3D point1 = getCoordinatesFromIndex(x + 1, y, z);
                Point3D point2 = getCoordinatesFromIndex(x, y + 1, z);
                Point3D point3 = getCoordinatesFromIndex(x, y, z + 1);

                shapePoints += handleShapePoint(reference, point1, getProperty(x,y,z), getProperty(x+1,y,z));
                shapePoints += handleShapePoint(reference, point2, getProperty(x,y,z), getProperty(x,y+1,z));
                shapePoints += handleShapePoint(reference, point3, getProperty(x,y,z), getProperty(x,y,z+1));
            }
        }
    }

    return shapePoints;
}

QVector<Point3D> Grid3D::handleShapePoint(const Point3D &reference, const Point3D &other, double referenceDistance, double otherDistance) const
{
    QVector<Point3D> newPoint;

    if (referenceDistance == (otherDistance == 0)) {
        newPoint.push_back(reference);
    } else {
        double t;

        if (otherDistance <= 0 && referenceDistance > 0) {
            t = referenceDistance / (referenceDistance - otherDistance);
            newPoint.push_back(reference.getPointOnEdge(other, t));
        }

        if (otherDistance >= 0 && referenceDistance < 0) {
            t = otherDistance / (otherDistance - referenceDistance);
            newPoint.push_back(other.getPointOnEdge(reference, t));
        }
    }

    return newPoint;
}

Point3D Grid3D::getCoordinatesFromIndex(int x, int y, int z) const
{
    return Point3D(origin.getX() + x,
                   origin.getY() + y,
                   origin.getZ() + z);
}


