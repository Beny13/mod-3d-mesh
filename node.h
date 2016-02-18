#ifndef NODE_H
#define NODE_H

#include <QtCore>

#include "point3d.h"

class Node
{
public:
    Node();
    Node(double x, double y, double z);
    void addTriangle(int triangle);
    void addNode(int node);

    const Point3D &getPoint() const;
    void setPoint(const Point3D &value);

    QVector<int> getTriangles() const;

    QVector<int> getNodes() const;

    Node translate(Point3D normal, double dPoint) const;

private:
    QVector<int> triangles;
    QVector<int> nodes;
    Point3D point;
};

#endif // NODE_H
