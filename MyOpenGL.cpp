#include "stdafx.h"

MyOpenGL::MyOpenGL() : QOpenGL3D()
{

}

MyOpenGL::~MyOpenGL()
{

}

void MyOpenGL::initializeGL()
{
   invalidate();
}

void MyOpenGL::paintGL()
{

    //clear OPENGL Window
    glClearColor(m_fbgRed, m_fbgGreen, m_fbgBlue, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    //
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //
    if(m_bOrtho)
    {
        glOrtho(m_fleft, m_fright, m_fbottom, m_ftop, m_fnear, m_ffar);
    }
    else if(m_bFrustum)
    {
        glFrustum(m_fleft, m_fright, m_fbottom, m_ftop, m_fnear, m_ffar);
    }
    else if(m_bPerspective)
    {
        gluPerspective(m_fangle, m_faspect, m_fnear, m_ffar);
    }

    //
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //camera setup
    gluLookAt(
         m_Pposition.x(),   m_Pposition.y(),    m_Pposition.z(),
         m_Ptarget.x(),     m_Ptarget.y(),      m_Ptarget.z(),
         m_VviewingUp.a(),  m_VviewingUp.b(),   m_VviewingUp.c()
    );

    //draw!
    mGrafik.Draw();
}



void MyOpenGL::resizeGL(int w, int h)
{
    int size = 0;
    w > h ? size = w : size = h;
    glViewport(0,0,size,size);
    update();
}
