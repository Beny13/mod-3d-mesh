#include <QtCore>

#include "point3d.h"
#include "surface3d.h"
#include "triangle.h"
#include "grid3d.h"
#include "sphere3d.h"
#include "doublesphere.h"
#include "meshfilemanager.h"

void testSurface() {
    // Testing writing & reading
    qDebug() << "Reading file..." << endl;
    Surface3D original = MeshFileManager::readSurface("/meshes/bunny.mesh");
    qDebug() << "Writing file..." << endl;
    MeshFileManager::writeSurface(original, "/rendering/render.mesh");
    qDebug() << "Loading written..." << endl;
    MeshFileManager::readSurface("/rendering/render.mesh");

    // Normal
    qDebug() << "Normalizing..." << endl;
    Surface3D norm = original.getNormalizedSurface();
    qDebug() << "Writing normalized..." << endl;
    MeshFileManager::writeSurface(norm, "/rendering/normalized.mesh");

    qDebug() << "max original point : " << original.getMaxPoint();
    qDebug() << "min original point : " << original.getMinPoint();
    qDebug() << "max normalized point : " << norm.getMaxPoint();
    qDebug() << "min normalized point : " << norm.getMinPoint();
    qDebug() << "average node neighbors : " << original.getAverageNeighbors();
    qDebug() << "average triangle neighbors : " << original.getAverageNeighborsTriangle();

}

void testGrid()
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
}

void testSphere()
{
    Grid3D grid(0, 0, 0, 50, 50, 50);

    qDebug() << "Testing sphere..." << endl;
    Sphere3D sphere3d(Point3D(25,25,25), 10);

    qDebug() << sphere3d.getRelativeDistance(Point3D(10,10,10))
             << sphere3d.getRelativeDistance(Point3D(10,0,0))
             << endl;

    qDebug() << "Testing sphere with grid..." << endl;

    grid.setShape(sphere3d);
    qDebug() << grid.getProperty(9, 0, 0)
             << grid.getProperty(0, 9, 0)
             << grid.getProperty(0, 0, 9)
             << grid.getProperty(9, 9, 9)
             << grid.getProperty(1, 0, 0)
             << endl;

    MeshFileManager::writeShape(grid, "/rendering/sphere.mesh");
    MeshFileManager::writeShapePoints(grid, "/rendering/sphere2.mesh");
}

int main(int argc, char *argv[])
{
    Grid3D grid(0, 0, 0, 50, 50, 50);

    DoubleSphere doubleSphere(Sphere3D(Point3D(25,25,25), 10), Sphere3D(Point3D(25,25,35), 10));

    grid.setShape(doubleSphere);

    MeshFileManager::writeShapePoints(grid, "/rendering/doublesphere.mesh");

    return 0;
}
