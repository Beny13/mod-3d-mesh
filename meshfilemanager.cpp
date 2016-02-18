#include "meshfilemanager.h"

#include "hexaedra.h"
#include "triangle.h"

MeshFileManager::MeshFileManager()
{
}

QString MeshFileManager::getRootPath()
{
    return QString("/home/ben/3d");
}

void MeshFileManager::writeShapePoints(const Grid3D &grid, const QString &path)
{
    QVector<Point3D> points = grid.getShapePoints();

    QFile file(getRootPath() + path);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream stream(&file);
    stream  << "MeshVersionFormatted 1" << endl
            << "Dimension" << endl
            << "3" << endl;

    stream  << "Vertices" << endl
            << points.size() << endl;

    for (int i = 0; i < points.size(); ++i) {
        stream << points[i].format()
               << endl;
    }

    stream << "End" << endl;
}

void MeshFileManager::writeShape(const Grid3D &grid, const QString &path)
{
    QFile file(getRootPath() + path);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream stream(&file);
    stream  << "MeshVersionFormatted 1" << endl
            << "Dimension" << endl
            << "3" << endl;

    stream  << "Vertices" << endl
            <<  grid.getNx() * grid.getNy() * grid.getNz() << endl;

    for (int z = 0; z < grid.getNz(); ++z) {
        for (int y = 0; y < grid.getNy(); ++y) {
            for (int x = 0; x < grid.getNx(); ++x) {
                Point3D currentPoint(grid.getOrigin().getX() + x,
                                     grid.getOrigin().getY() + y,
                                     grid.getOrigin().getZ() + z);

                if (grid.getProperty(currentPoint.getX(), currentPoint.getY(), currentPoint.getZ()) < 0) {
                    stream << currentPoint.format()
                           << endl;
                }
            }
        }
    }

    stream << "End" << endl;
}


void MeshFileManager::writeGeometry(const Grid3D &grid, const QString &path)
{
    QFile file(getRootPath() + path);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream stream(&file);
    stream  << "MeshVersionFormatted 1" << endl
            << "Dimension" << endl
            << "3" << endl;

    int nx = grid.getNx();
    int ny = grid.getNy();
    int nz = grid.getNz();
    Point3D origin = grid.getOrigin();

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

Surface3D MeshFileManager::readSurface(const QString &path)
{
    // Opening the file
    QFile file(getRootPath() + path);
    if(!file.open(QIODevice::ReadOnly)) {
        return Surface3D();
    }

    QTextStream in(&file);

    // Skipping useless lines
    in.readLine();
    in.readLine();
    in.readLine();
    in.readLine();

    // The full surface
    Surface3D surface;

    // Vertices
    int verticesCount = in.readLine().toInt();
    for (int i = 0; i < verticesCount; ++i) {
        QString line = in.readLine().trimmed();
        QStringList fields = line.split(" ");
        surface.addNode(Node(fields[0].toDouble(), fields[1].toDouble(), fields[2].toDouble()));
    }

    // Triangles
    in.readLine(); // Skipping "Triangles"
    int trianglesCount = in.readLine().toInt();
    for (int i = 0; i < trianglesCount; ++i) {
        QString line = in.readLine().trimmed();
        QStringList fields = line.split(" ");
        surface.addTriangle(Triangle(fields[0].toInt() - 1, fields[1].toInt() - 1, fields[2].toInt() - 1));
    }

    file.close();

    return surface;
}

void MeshFileManager::writeSurface(const Surface3D &surface, const QString &path)
{
    QFile file(getRootPath() + path);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream stream(&file);
    stream  << "MeshVersionFormatted 1" << endl
            << "Dimension" << endl
            << "3" << endl;

    // Writing vertices
    int pointsCount = surface.getPointsCount();

    stream  << "Vertices" << endl
            << pointsCount << endl;

    for (int i = 0; i < pointsCount; ++i) {
        stream << surface.getPoint(i).format() << endl;
    }

    // Writing triangles
    int triangleCount = surface.getTrianglesCount();

    stream  << "Triangles" << endl
            << triangleCount << endl;

    for (int i = 0; i < triangleCount; ++i) {
        stream << surface.getTriangle(i).format() << endl;
    }

    stream << "End" << endl;
}
