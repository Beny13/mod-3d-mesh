#include <QtCore>

#include "point3d.h"
#include "surface3d.h"
#include "triangle.h"
#include "grid3d.h"
#include "sphere3d.h"

void testSurface(){
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

}

int main(int argc, char *argv[])
{
    qDebug() << "Creating grid..." << endl;
    Grid3D grid(0, 0, 0, 50, 50, 50);

    qDebug() << "Rendering grid..." << endl;
    grid.writeToFile("/home/ben/3d/rendering/generatedGrid.mesh");

    qDebug() << grid.getProperties().size()
             << grid.getProperties()[0].size()
             << grid.getProperties()[0][0].size()
             << endl;

    qDebug() << grid.getProperty(1, 2, 3);
    grid.setProperty(1, 2, 3, 10.5);
    qDebug() << grid.getProperty(1, 2, 3);

    qDebug() << "Testing sphere..." << endl;
    Sphere3D sphere3d(Point3D(20,20,20), 15);

    qDebug() << sphere3d.getRelativeDistance(Point3D(10,10,10))
             << sphere3d.getRelativeDistance(Point3D(10,0,0))
             << endl;

    qDebug() << "Testing sphere with grid..." << endl;

    grid.setPropertiesFromSphere(sphere3d);
    qDebug() << grid.getProperty(9, 0, 0)
             << grid.getProperty(0, 9, 0)
             << grid.getProperty(0, 0, 9)
             << grid.getProperty(9, 9, 9)
             << grid.getProperty(1, 0, 0)
             << endl;

    grid.writeToFile("/home/ben/3d/rendering/sphere.mesh", sphere3d);

    return 0;
}
