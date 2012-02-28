#include <QtOpenGL>
#include <QGLWidget>
#include "Grafik.h"

class QOpenGL : public QGLWidget
{

public:
    QOpenGL();
    virtual ~QOpenGL();

public:
	bool InitOpenGL(char*, int x_left, int x_right, int y_top, int y_bottom);
	void setGrafik(CGrafik*);
	void setWindow(GLfloat x_min, GLfloat x_max, GLfloat y_min, GLfloat y_max);
	void getWindow(GLfloat* x_min, GLfloat* x_max, GLfloat* y_min, GLfloat* y_max);
    float getRatio();
	void setBackGround(GLfloat, GLfloat, GLfloat);
    void invalidate();

protected:	
    GLfloat m_fbgRed, m_fbgGreen, m_fbgBlue;
    GLfloat m_fxmin, m_fxmax, m_fymin, m_fymax;
    CGrafik* m_pGrafik;
};


