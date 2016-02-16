#ifndef SURFACE3D_H
#define SURFACE3D_H

#include <QVector>

#include "triangle.h"
#include "point3d.h"

class Surface3D
{
public:
    Surface3D();
    void addPoint(const Point3D & point);
    void addTriangle(const Triangle & triangle);
    int getTrianglesCount();
    int getPointsCount();

    // File handling
    static Surface3D loadFromFile(const QString & path);
    void writeToFile(const QString & path);

    // Min/Max
    Point3D getMinPoint();
    Point3D getMaxPoint();

    // Normal
    Point3D computeTriangleNormal(int triangleIndex);
    Point3D computeNodeNormal(int nodeIndex);
    double computeDPoint();
    Surface3D getNormalizedSurface();
private:
    /*int nb_nodes;
    int nb_facets;*/
    QVector<Triangle> triangles;
    QVector<Point3D> points;
};

#endif // SURFACE3D_H
