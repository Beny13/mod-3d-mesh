#include "surface3d.h"

#include <QtCore>

Surface3D::Surface3D()
{
}

void Surface3D::addPoint(const Point3D &point)
{
    points.push_back(point);
}

void Surface3D::addTriangle(const Triangle &triangle)
{
    triangles.push_back(triangle);
}

int Surface3D::getTrianglesCount()
{
    return triangles.size();
}

int Surface3D::getPointsCount()
{
    return points.size();
}

Surface3D Surface3D::loadFromFile(const QString &path)
{
    // Opening the file
    QFile file(path);
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
        surface.addPoint(Point3D(fields[0].toDouble(), fields[1].toDouble(), fields[2].toDouble()));
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

void Surface3D::writeToFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream stream(&file);
    stream  << "MeshVersionFormatted 1" << endl
            << "Dimension" << endl
            << "3" << endl;

    // Writing vertices
    int pointsCount = getPointsCount();

    stream  << "Vertices" << endl
            << pointsCount << endl;

    for (int i = 0; i < pointsCount; ++i) {
        stream << " " << points[i].getX() << " " << points[i].getY() << " " << points[i].getZ() << " 0" << endl;
    }

    // Writing triangles
    int triangleCount = getTrianglesCount();

    stream  << "Triangles" << endl
            << triangleCount << endl;

    for (int i = 0; i < triangleCount; ++i) {
        stream << " " << triangles[i].getIndex1() + 1 << " " << triangles[i].getIndex2() + 1 << " " << triangles[i].getIndex3() + 1 << " 508" << endl;
    }

    stream << "End" << endl;

}

Point3D Surface3D::getMinPoint()
{
    double minX = points[0].getX();
    double minY = points[0].getY();
    double minZ = points[0].getZ();

    for (int i = 1; i < getPointsCount(); ++i) {
        if (minX > points[i].getX())
            minX = points[i].getX();

        if (minY > points[i].getY())
            minY = points[i].getY();

        if (minZ > points[i].getZ())
            minZ = points[i].getZ();
    }

    return Point3D(minX, minY, minZ);
}

Point3D Surface3D::getMaxPoint()
{
    double maxX = points[0].getX();
    double maxY = points[0].getY();
    double maxZ = points[0].getZ();

    for (int i = 1; i < getPointsCount(); ++i) {
        if (maxX < points[i].getX())
            maxX = points[i].getX();

        if (maxY < points[i].getY())
            maxY = points[i].getY();

        if (maxZ < points[i].getZ())
            maxZ = points[i].getZ();
    }

    return Point3D(maxX, maxY, maxZ);
}

Point3D Surface3D::computeTriangleNormal(int triangleIndex)
{
    Triangle triangle = triangles[triangleIndex];

    Point3D point1 = points[triangle.getIndex1()];
    Point3D point2 = points[triangle.getIndex2()];
    Point3D point3 = points[triangle.getIndex3()];

    return Point3D(
        (point2.getY() - point1.getY()) * (point3.getZ() - point1.getZ()) - (point2.getZ() - point1.getZ()) * (point3.getY() - point1.getY()),
        (point2.getZ() - point1.getZ()) * (point3.getX() - point1.getX()) - (point2.getX() - point1.getX()) * (point3.getZ() - point1.getZ()),
        (point2.getX() - point1.getX()) * (point3.getY() - point1.getY()) - (point2.getY() - point1.getY()) * (point3.getX() - point1.getX())
    );

}

Point3D Surface3D::computeNodeNormal(int nodeIndex)
{
    int triangleCount = 0;
    double x = 0, y = 0, z = 0;

    for (int i = 0; i < getTrianglesCount(); ++i) {
        if (triangles[i].hasIndex(nodeIndex)) {
            Point3D currentNormal = computeTriangleNormal(i);
            x += currentNormal.getX();
            y += currentNormal.getY();
            z += currentNormal.getZ();

            ++triangleCount;
        }
    }

    return Point3D(x / triangleCount, y / triangleCount, z / triangleCount);
}

double Surface3D::computeDPoint()
{
    return 100.;
}

Surface3D Surface3D::getNormalizedSurface()
{
    Surface3D result;
    result.triangles = triangles;
    double dPoint = computeDPoint();

    for (int i = 0; i < getPointsCount(); ++i) {
        result.addPoint(points[i].translate(computeNodeNormal(i), dPoint));
    }

    return result;
}
