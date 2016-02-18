#ifndef MESHFILEMANAGER_H
#define MESHFILEMANAGER_H

#include "grid3d.h"
#include "surface3d.h"

class MeshFileManager
{
public:
    MeshFileManager();

    static QString getRootPath();

    static void writeShapePoints(const Grid3D & grid, const QString &path);
    static void writeShape(const Grid3D &grid, const QString &path);
    static void writeGeometry(const Grid3D &grid, const QString &path);

    static Surface3D readSurface(const QString &path);
    static void writeSurface(const Surface3D &surface, const QString &path);
};

#endif // MESHFILEMANAGER_H
