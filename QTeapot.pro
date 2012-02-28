#-------------------------------------------------
#
# Project created by QtCreator 2012-02-24T16:04:33
#
#-------------------------------------------------

QT       += opengl

TARGET = QTeapot
TEMPLATE = app


SOURCES += main.cpp\
    Class3D/CVector3d.cpp \
    Class3D/CPoint3d.cpp \
    Grafik.cpp \
    OpenGL/QOpenGL3D.cpp \
    OpenGL/QOpenGL.cpp \
    QTeapotDlg.cpp \
    MyOpenGL.cpp

HEADERS  += \
    Class3D/CVector3d.h \
    Class3D/CPoint3d.h \
    Grafik.h \
    OpenGL/QOpenGL3D.h \
    OpenGL/QOpenGL.h \
    QTeapotDlg.h \
    MyOpenGL.h

FORMS    += mainwindow.ui

LIBS += -lGL -lglut -lGLU
LIBS += -L/usr/lib/libglut.so
