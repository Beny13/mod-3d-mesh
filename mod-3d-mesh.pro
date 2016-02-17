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
    hexaedra.cpp

HEADERS += \
    surface3d.h \
    triangle.h \
    point3d.h \
    node.h \
    grid3d.h \
    hexaedra.h
