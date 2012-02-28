#include <QGLWidget>
#include "Class3D/CPoint3d.h"
#include "Class3D/CVector3d.h"
#include "Grafik.h"
#include "GL/glu.h"
#include "OpenGL/QOpenGL3D.h"

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
        CGrafik mGrafik;
};
