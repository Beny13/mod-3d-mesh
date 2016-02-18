#-------------------------------------------------
#
# Project created by QtCreator 2016-02-15T13:59:40
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = mod-3d-mesh
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    surface3d.cpp \
    triangle.cpp \
    point3d.cpp \
    node.cpp \
    grid3d.cpp \
    hexaedra.cpp \
    sphere3d.cpp \
    implicitobject.cpp \
    doublesphere.cpp \
    meshfilemanager.cpp \
    plane.cpp \
    multisphere.cpp

HEADERS += \
    surface3d.h \
    triangle.h \
    point3d.h \
    node.h \
    grid3d.h \
    hexaedra.h \
    sphere3d.h \
    implicitobject.h \
    doublesphere.h \
    meshfilemanager.h \
    plane.h \
    multisphere.h
