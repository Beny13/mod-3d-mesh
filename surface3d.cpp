#include "surface3d.h"

#include <QtCore>

Surface3D::Surface3D()
{
}

void Surface3D::addNode(const Node & node)
{
    nodes.push_back(node);
}

double Surface3D::getAverageNeighbors()
{
    double res = 0;
    for(int i = 0; i < nodes.size(); ++i){
        res += nodes[i].getNodes().size();
    }
    return res/nodes.size();
}

double Surface3D::getAverageNeighborsTriangle()
{
    double res = 0;
    for(int i = 0; i < nodes.size(); ++i){
        res += nodes[i].getTriangles().size();
    }
    return res/nodes.size();
}

Triangle Surface3D::getTriangle(int i) const
{
    return triangles[i];
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

int Surface3D::getTrianglesCount() const
{
    return triangles.size();
}

int Surface3D::getPointsCount() const
{
    return nodes.size();
}

const Point3D &Surface3D::getPoint(int i) const
{
    return nodes[i].getPoint();
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

    double x1 = point1.getX();
    double y1 = point1.getY();
    double z1 = point1.getZ();

    double x2 = point2.getX();
    double y2 = point2.getY();
    double z2 = point2.getZ();

    double x3 = point3.getX();
    double y3 = point3.getY();
    double z3 = point3.getZ();

    return Point3D(
        (y2 - y1) * (z3 - z1) - (z2 - z1) * (y3 - y1),
        (z2 - z1) * (x3 - x1) - (x2 - x1) * (z3 - z1),
        (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)
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
