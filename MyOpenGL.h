#ifndef MYOPENGL_H
#define MYOPENGL_H

#include "OpenGL/QOpenGL3D.h"

/**
 *
 */
class MyOpenGL : public QOpenGL3D
{

    public:
        MyOpenGL();
        ~MyOpenGL();

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);

    private:
        CGraphic mGrafik;
};

#endif
