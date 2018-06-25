QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = e8yescg

TEMPLATE = app

#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE += -Ofast -flto

#QMAKE_LFLAGS_RELEASE += -Ofast -flto -march=native

CONFIG += c++14

SOURCES += src/main.cpp \
    src/camera.cpp \
    src/tensor.cpp \
    src/geometry.cpp \
    src/light.cpp \
    src/scene.cpp \
    src/renderer.cpp \
    src/material.cpp \
    test/test.cpp \
    test/testrunner.cpp \
    test/testtensor.cpp \
    src/resource.cpp \
    src/pathtracer.cpp \
    src/raster.cpp \
    src/frame.cpp \
    test/testgeometry.cpp \
    src/thread.cpp \
    src/app.cpp \
    src/compositor.cpp \
    test/testresource.cpp \
    test/testcamera.cpp \
    test/testframe.cpp \
    test/testscene.cpp \
    test/testdirectrenderer.cpp \
    test/testunidirectrenderer.cpp \
    test/testbidirectrenderer.cpp

HEADERS += \
    src/scene.h \
    src/camera.h \
    src/tensor.h \
    src/geometry.h \
    src/light.h \
    src/renderer.h \
    test/test.h \
    src/material.h \
    test/testrunner.h \
    test/testtensor.h \
    src/resource.h \
    src/pathtracer.h \
    src/raster.h \
    src/frame.h \
    test/testgeometry.h \
    src/thread.h \
    src/app.h \
    src/compositor.h \
    test/testresource.h \
    test/testcamera.h \
    test/testframe.h \
    test/testscene.h \
    test/testdirectrenderer.h \
    test/testunidirectrenderer.h \
    test/testbidirectrenderer.h

#LIBS += -lGLEW
#LIBS += -lglfw
#LIBS += -lglut
#LIBS += -lGL
#LIBS += -lGLU
CONFIG += link_pkgconfig
PKGCONFIG += opencv

FORMS += \
    src/mainwindow.ui
