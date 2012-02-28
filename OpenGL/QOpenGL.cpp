// OpenGL.cpp : Implementierungsdatei
//
#include "QOpenGL.h"
#include <GL/glut.h>
#include <QGLFormat>

QOpenGL::QOpenGL() : QGLWidget()
{
	m_fbgRed = 1; m_fbgGreen = 1; m_fbgBlue = 1;
	m_fxmin = -50;
	m_fxmax = 50;
	m_fymin = -50;
	m_fymax = 50;
	m_pGrafik = NULL;
}

QOpenGL::~QOpenGL()
{

}

bool QOpenGL::InitOpenGL(char* text, int x_left, int x_right, int y_top, int y_bottom)
{

    int argc = 0;
    char** argv = 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    this->setWindowTitle(QString(text));
    this->setBaseSize(x_right-x_left,y_bottom-y_top);
    this->move(x_left,y_top);

    return false;  // Melde: Hier ist was schief gelaufen
}

void QOpenGL::setGrafik(CGrafik* grafik)
{
    m_pGrafik = grafik;
}

void QOpenGL::setWindow(GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax)
{
	m_fxmin = xmin;
	m_fxmax = xmax;
	m_fymin = ymin;
	m_fymax = ymax;
}

void QOpenGL::getWindow(GLfloat* xmin, GLfloat* xmax, GLfloat* ymin, GLfloat* ymax)
{
	*xmin = m_fxmin;
	*xmax = m_fxmax;
	*ymin = m_fymin;
	*ymax = m_fymax;
}

void QOpenGL::setBackGround(GLfloat bgRed, GLfloat bgGreen, GLfloat bgBlue)
{
	m_fbgRed   = bgRed;
	m_fbgGreen = bgGreen;
	m_fbgBlue  = bgBlue;
}

float QOpenGL::getRatio()
{
    return (m_fxmax - m_fxmin) / (m_fymax - m_fymax);
}


void QOpenGL::invalidate()
{
    //m_pGrafik->Draw();
    this->paintGL();
    this->update();
}
