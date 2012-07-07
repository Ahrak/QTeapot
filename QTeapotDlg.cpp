#include <QtGui>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <math.h>
#include <iostream>
#include "QTeapotDlg.h"

QTeapotDlg::QTeapotDlg(MyOpenGL* openGL, QWidget* parent)
    : QDockWidget(parent)
    , ui(new Ui::OpenGLCamDialog)
    , m_glWidget(openGL)
    , m_centralWidget(new QWidget(this))
    //
    , m_zoom(10)
    , m_posXY(45)
    , m_posZ(45)
    //
    , m_camX(0)
    , m_camY(0)
    , m_camZ(0)
{

    //QT STUFF
    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    this->setWidget(m_centralWidget);
    ui->setupUi(m_centralWidget);
    this->move(520,0);

    //size of control window
    this->setFixedSize(300,400);
    this->setWindowTitle("Camera Control");

    //Position
    ui->editPX->setText(QString("%1").arg(m_camX));
    ui->editPY->setText(QString("%1").arg(m_camY));
    ui->editPZ->setText(QString("%1").arg(m_camZ));

    //Zoom
    ui->lblZoom->setText(QString("%1").arg(m_zoom));
    ui->slideZoom->setRange(0,30);
    ui->slideZoom->setTickInterval(1);
    ui->slideZoom->setSliderPosition(m_zoom);

    //XY
    ui->slideXY->setRange(0,360);
    ui->slideXY->setTickInterval(9);
    ui->slideXY->setSliderPosition(m_posXY);

    //Z
    ui->slideZ->setRange(-90,90);
    ui->slideZ->setTickInterval(9);
    ui->slideZ->setSliderPosition(m_posZ);

    //Signals
    QObject::connect(ui->slideZoom, SIGNAL( valueChanged(int)), this, SLOT( changeZoom(int) ));
    QObject::connect(ui->slideXY, SIGNAL( valueChanged(int)), this, SLOT( changeXY(int) ));
    QObject::connect(ui->slideZ, SIGNAL( valueChanged(int)), this, SLOT( changeZ(int) ));
    QObject::connect(ui->btnLookAt, SIGNAL( pressed()), this, SLOT( changeLookAt() ));
    QObject::connect(this, SIGNAL( cameraChanged()), this, SLOT( onCamera() ));

    //
    emit cameraChanged();
    m_glWidget->ortho(-m_zoom, m_zoom, -m_zoom, m_zoom, -100000, 100000);


}

QTeapotDlg::~QTeapotDlg()
{
    delete ui;
}


void QTeapotDlg::changeZoom(int zoom)
{
    this->m_zoom = zoom;
    ui->lblZoom->setText(QString("%1").arg(zoom));
    m_glWidget->ortho(-m_zoom, m_zoom, -m_zoom, m_zoom, -100000, 100000);
    emit cameraChanged();
}

void QTeapotDlg::changeXY(int xy)
{
    m_posXY = xy;
    ui->lblXY->setText(QString("%1").arg(xy));
    emit cameraChanged();
}

void QTeapotDlg::changeZ(int z)
{
    m_posZ = z;
    ui->lblZ->setText(QString("%1").arg(z));
    emit cameraChanged();
}


void QTeapotDlg::changeLookAt()
{
    m_camX = ui->editPX->text().toFloat();
    m_camY = ui->editPY->text().toFloat();
    m_camZ = ui->editPZ->text().toFloat();

    out(QString("New lookAt point: (%1, %2, %3)")
        .arg(m_camX).arg(m_camY).arg(m_camZ));

    emit cameraChanged();
}


void QTeapotDlg::onClose()
{
    this->close();
    m_glWidget->close();
}

void QTeapotDlg::onCamera() {

    float winkel_XY, winkel_Z;
    float xx, yy, zz;

    //deg --> rad
    winkel_XY = m_posXY/180 * M_PI;
    winkel_Z = m_posZ/180 * M_PI;

    //calc new camera position
    xx = m_camX + cos(winkel_Z) * cos(winkel_XY);
    yy = m_camY + cos(winkel_Z) * sin(winkel_XY);
    zz = m_camZ + sin(winkel_Z);

    //set new camera position
    Point3D camPos(xx, yy, zz);

    if( fabs(sin(winkel_Z))<0.999)
    {
        m_glWidget->lookAt(
            camPos,
            Point3D(m_camX, m_camY, m_camZ),
            Vector3D(0,0,1)
        );
    }
    else if (sin(winkel_Z)>0)
    {
        m_glWidget->lookAt(
            camPos,
            Point3D(m_camX, m_camY, m_camZ-1),
            Vector3D(-cos(winkel_XY),-sin(winkel_XY),0)
        );
    }
    else
    {
        m_glWidget->lookAt(
            camPos,
            Point3D(m_camX, m_camY, m_camZ+1),
            Vector3D(cos(winkel_XY),sin(winkel_XY),0)
        );
    }
    //redraw
    m_glWidget->invalidate();
}


void QTeapotDlg::out(QString line)
{
    ui->log->append(line);
}
