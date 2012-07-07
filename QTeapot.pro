#-------------------------------------------------
#
# Project created by QtCreator 2012-02-24T16:04:33
#
#-------------------------------------------------

QT       += core gui opengl p

TARGET = QTeapot
TEMPLATE = app
LANGUAGE = C++
CONFIG   += console precompile_header

PRECOMPILED_HEADER = stdafx.h

SOURCES += main.cpp\
    Class3D/CVector3d.cpp \
    Class3D/CPoint3d.cpp \
    OpenGL/QOpenGL3D.cpp \
    OpenGL/QOpenGL.cpp \
    Grafik.cpp \
    QTeapotDlg.cpp \
    MyOpenGL.cpp \
    mainwindow.cpp

HEADERS  += stdafx.h \
    Class3D/CVector3d.h \
    Class3D/CPoint3d.h \
    Grafik.h \
    OpenGL/QOpenGL3D.h \
    OpenGL/QOpenGL.h \
    QTeapotDlg.h \
    MyOpenGL.h \
    mainwindow.h \
    stdafx.h

FORMS    += mainwindow.ui \
    dialog.ui

LIBS += -lGL -lglut -lGLU
LIBS += -L/usr/lib/libglut.so

OTHER_FILES +=
