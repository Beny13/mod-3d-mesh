#include <QtCore>

#include "point3d.h"
#include "surface3d.h"
#include "triangle.h"

int main(int argc, char *argv[])
{
    Surface3D original = Surface3D::loadFromFile("/home/ben/3d/meshes/bunny.mesh");
    // Testing writing & reading
    original.writeToFile("/home/ben/3d/science/render.mesh");

    Surface3D yolo = Surface3D::loadFromFile("/home/ben/3d/science/render.mesh");

    // Min & max
    Point3D max = yolo.getMaxPoint();
    Point3D min = yolo.getMinPoint();



    // Normal
    Surface3D norm = original.getNormalizedSurface();
    norm.writeToFile("/home/ben/3d/science/normalized.mesh");

    qDebug() << original.getMaxPoint() << original.getMinPoint() << endl  << norm.getMaxPoint() << norm.getMinPoint();

    return 0;
}
