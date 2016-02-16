#include "surface3d.h"

#include <QtCore>

Surface3D::Surface3D()
{
}

void Surface3D::addNode(const Node & node)
{
    nodes.push_back(node);
}

void Surface3D::setNode(int source, int neighbour1, int neighbour2)
{
    nodes[source].addTriangle(triangles.size());
    nodes[source].addNode(neighbour1);
    nodes[source].addNode(neighbour2);
}

void Surface3D::addTriangle(const Triangle &triangle)
{
    int node1 = triangle.getIndex1();
    int node2 = triangle.getIndex2();
    int node3 = triangle.getIndex3();

    setNode(node1, node2, node3);
    setNode(node2, node1, node3);
    setNode(node3, node1, node2);
    triangles.push_back(triangle);
}

int Surface3D::getTrianglesCount()
{
    return triangles.size();
}

int Surface3D::getPointsCount()
{
    return nodes.size();
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
        stream << " " << nodes[i].getPoint().getX() << " " << nodes[i].getPoint().getY() << " " << nodes[i].getPoint().getZ() << " 0" << endl;
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
    double minX = nodes[0].getPoint().getX();
    double minY = nodes[0].getPoint().getY();
    double minZ = nodes[0].getPoint().getZ();

    for (int i = 1; i < getPointsCount(); ++i) {
        if (minX > nodes[i].getPoint().getX())
            minX = nodes[i].getPoint().getX();

        if (minY > nodes[i].getPoint().getY())
            minY = nodes[i].getPoint().getY();

        if (minZ > nodes[i].getPoint().getZ())
            minZ = nodes[i].getPoint().getZ();
    }

    return Point3D(minX, minY, minZ);
}

Point3D Surface3D::getMaxPoint()
{
    double maxX = nodes[0].getPoint().getX();
    double maxY = nodes[0].getPoint().getY();
    double maxZ = nodes[0].getPoint().getZ();

    for (int i = 1; i < getPointsCount(); ++i) {
        if (maxX < nodes[i].getPoint().getX())
            maxX = nodes[i].getPoint().getX();

        if (maxY < nodes[i].getPoint().getY())
            maxY = nodes[i].getPoint().getY();

        if (maxZ < nodes[i].getPoint().getZ())
            maxZ = nodes[i].getPoint().getZ();
    }

    return Point3D(maxX, maxY, maxZ);
}

Point3D Surface3D::computeTriangleNormal(int triangleIndex)
{
    Triangle triangle = triangles[triangleIndex];

    Point3D point1 = nodes[triangle.getIndex1()].getPoint();
    Point3D point2 = nodes[triangle.getIndex2()].getPoint();
    Point3D point3 = nodes[triangle.getIndex3()].getPoint();

    return Point3D(
        (point2.getY() - point1.getY()) * (point3.getZ() - point1.getZ()) - (point2.getZ() - point1.getZ()) * (point3.getY() - point1.getY()),
        (point2.getZ() - point1.getZ()) * (point3.getX() - point1.getX()) - (point2.getX() - point1.getX()) * (point3.getZ() - point1.getZ()),
        (point2.getX() - point1.getX()) * (point3.getY() - point1.getY()) - (point2.getY() - point1.getY()) * (point3.getX() - point1.getX())
    );

}

Point3D Surface3D::computeNodeNormal(int nodeIndex)
{
    double x = 0, y = 0, z = 0;

    int nbTriangles = nodes[nodeIndex].getTriangles().size();

    if (nbTriangles == 0) {
        return Point3D(0, 0, 0);
    }

    for (int i = 0; i < nbTriangles; ++i) {
        Point3D currentNormal = computeTriangleNormal(nodes[nodeIndex].getTriangles().at(i));
        x += currentNormal.getX();
        y += currentNormal.getY();
        z += currentNormal.getZ();
    }

    Point3D point(x / nbTriangles, y / nbTriangles, z / nbTriangles);
    double l = sqrt(point.getX() * point.getX() + point.getY() * point.getY() + point.getZ() * point.getZ());

    return Point3D(point.getX() / l, point.getY() / l, point.getZ() / l);
}

double Surface3D::computeDPoint()
{
    return 0.01;
}

Surface3D Surface3D::getNormalizedSurface()
{
    Surface3D result;
    result.triangles = triangles;
    double dPoint = computeDPoint();

    for (int i = 0; i < getPointsCount(); ++i) {
        result.addNode(nodes[i].translate(computeNodeNormal(i), dPoint));
    }

    return result;
}
