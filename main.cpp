#include <QtCore>

#include "point3d.h"
#include "surface3d.h"
#include "triangle.h"

int main(int argc, char *argv[])
{
    QString rootFile("/home/ben/3d");

    qDebug() << "Reading file..." << endl;
    Surface3D original = Surface3D::loadFromFile(rootFile+"/meshes/bunny.mesh");
    // Testing writing & reading

    qDebug() << "Writing file..." << endl;
    original.writeToFile(rootFile+"/rendering/render.mesh");

    qDebug() << "Loading written..." << endl;
    Surface3D yolo = Surface3D::loadFromFile(rootFile+"/rendering/render.mesh");

    // Min & max
    Point3D max = yolo.getMaxPoint();
    Point3D min = yolo.getMinPoint();

    // Normal
    qDebug() << "Normalizing..." << endl;
    Surface3D norm = original.getNormalizedSurface();
    qDebug() << "Writing normalized..." << endl;
    norm.writeToFile(rootFile+"/rendering/normalized.mesh");

    qDebug() << "max original point : " << original.getMaxPoint();
    qDebug() << "min original point : " << original.getMinPoint();
    qDebug() << "max normalized point : " << norm.getMaxPoint();
    qDebug() << "min normalized point : " << norm.getMinPoint();
    qDebug() << "average node neighbors : " << original.getAverageNeighbors();
    qDebug() << "average triangle neighbors : " << original.getAverageNeighborsTriangle();

    return 0;
}
