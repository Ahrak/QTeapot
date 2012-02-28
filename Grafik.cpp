#include "Grafik.h"
#include <QtOpenGL>
#include <GL/glu.h>
#include <GL/glut.h>

CGrafik::CGrafik()
{

}

CGrafik::~CGrafik()
{

}

void CGrafik::Init()
{
    glNewList(1, GL_COMPILE);
        // Roter Teapot, Ausgiesser Richtung Osten
        glColor3f(1,0,0);
        glPushMatrix();
            glRotatef(90,1,0,0);
            glutWireTeapot(3);
        glPopMatrix();
        // Blauer Einheitswuerfel im Nullpunkt
        glColor3f(0,0,1);
        glutSolidCube(1);
        // Gelber Einheitswuerfel darueber
        glColor3f(1,1,0);
        glPushMatrix();
            glTranslatef(0,0,1);
            glutSolidCube(1);
        glPopMatrix();
        // Gruener Einheitswuerfel im Punkt (10,0,0)
        glColor3f(0,1,0);
        glPushMatrix();
            glTranslatef(10,0,0);
            glutSolidCube(1);
        glPopMatrix();
    glEndList();
}

void CGrafik::Draw()
{
    //Gouraud Schattierung
    glShadeModel(GL_SMOOTH);

    //Displayliste darstellen
    glCallList(1);
}
