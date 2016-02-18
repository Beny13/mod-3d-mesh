#ifndef SURFACE3D_H
#define SURFACE3D_H

#include <QVector>

#include "triangle.h"
#include "point3d.h"
#include "node.h"

class Surface3D
{
public:
    Surface3D();
    void addNode(const Node &node);
    void addTriangle(const Triangle & triangle);
    int getTrianglesCount() const;
    int getPointsCount() const;
    const Point3D & getPoint(int i) const;

    // Min/Max
    Point3D getMinPoint();
    Point3D getMaxPoint();

    // Normal
    Point3D computeTriangleNormal(int triangleIndex);
    Point3D computeNodeNormal(int nodeIndex);
    double computeDPoint();
    Surface3D getNormalizedSurface();
    void setNode(int source, int neighbour1, int neighbour2);
    double getAverageNeighbors();
    double getAverageNeighborsTriangle();

    Triangle getTriangle(int i) const;
private:
    QVector<Triangle> triangles;
    QVector<Node> nodes;
};

#endif // SURFACE3D_H
