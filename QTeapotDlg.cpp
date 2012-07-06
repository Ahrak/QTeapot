#include <QtGui>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <math.h>
#include <iostream>
#include "QTeapotDlg.h"

QTeapotDlg::QTeapotDlg(QWidget* parent)
    : QDockWidget(parent)
    , ui(new Ui::OpenGLCamDialog)
    , m_glWidget(0)
    , m_centralWidget(new QWidget(this))
    //
    , mZoom(10)
    , mPosXY(45)
    , mPosZ(45)
    //
    , mCamX(0)
    , mCamY(0)
    , mCamZ(0)
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
    ui->editPX->setText(QString("%1").arg(mCamX));
    ui->editPY->setText(QString("%1").arg(mCamY));
    ui->editPZ->setText(QString("%1").arg(mCamZ));

    //Zoom
    ui->lblZoom->setText(QString("%1").arg(mZoom));
    ui->slideZoom->setRange(0,30);
    ui->slideZoom->setTickInterval(1);
    ui->slideZoom->setSliderPosition(mZoom);

    //XY
    ui->slideXY->setRange(0,360);
    ui->slideXY->setTickInterval(9);
    ui->slideXY->setSliderPosition(mPosXY);

    //Z
    ui->slideZ->setRange(-90,90);
    ui->slideZ->setTickInterval(9);
    ui->slideZ->setSliderPosition(mPosZ);

    //Signals
    QObject::connect(ui->slideZoom, SIGNAL( valueChanged(int)), this, SLOT( changeZoom(int) ));
    QObject::connect(ui->slideXY, SIGNAL( valueChanged(int)), this, SLOT( changeXY(int) ));
    QObject::connect(ui->slideZ, SIGNAL( valueChanged(int)), this, SLOT( changeZ(int) ));
    QObject::connect(ui->btnLookAt, SIGNAL( pressed()), this, SLOT( changeLookAt() ));
    QObject::connect(this, SIGNAL( cameraChanged()), this, SLOT( onCamera() ));
    //QObject::connect(this, SIGNAL( destroyed()), this, SLOT(onClose()));
    //QObject::connect(glWidget, SIGNAL( destroyed()), this, SLOT(onClose()));


    //----------OPENGL WINDOW----------------
    m_glWidget = new MyOpenGL;
    m_glWidget->show();
    m_glWidget->InitOpenGL("QTeapot",0,500,0,500);
    m_glWidget->setGrafik(&mGrafik);
    mGrafik.Init();

    //
    emit cameraChanged();
    m_glWidget->ortho(-mZoom, mZoom, -mZoom, mZoom, -100000, 100000);
}

QTeapotDlg::~QTeapotDlg()
{
    delete ui;
}


void QTeapotDlg::changeZoom(int zoom)
{
    this->mZoom = zoom;
    ui->lblZ->setText(QString("%1").arg(zoom));
    m_glWidget->ortho(-mZoom, mZoom, -mZoom, mZoom, -100000, 100000);
    emit cameraChanged();
}

void QTeapotDlg::changeXY(int xy)
{
    mPosXY = xy;
    ui->lblXY->setText(QString("%1").arg(xy));
    emit cameraChanged();
}

void QTeapotDlg::changeZ(int z)
{
    mPosZ = z;
    ui->lblZ->setText(QString("%1").arg(z));
    emit cameraChanged();
}


void QTeapotDlg::changeLookAt()
{
    mCamX = ui->editPX->text().toFloat();
    mCamY = ui->editPY->text().toFloat();
    mCamZ = ui->editPZ->text().toFloat();

    out(QString("New lookAt point: (%1, %2, %3)")
        .arg(mCamX).arg(mCamY).arg(mCamZ));

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
    winkel_XY = mPosXY/180 * M_PI;
    winkel_Z = mPosZ/180 * M_PI;

    //calc new camera position
    xx = mCamX + cos(winkel_Z) * cos(winkel_XY);
    yy = mCamY + cos(winkel_Z) * sin(winkel_XY);
    zz = mCamZ + sin(winkel_Z);

    //set new camera position
    Point3D camPos(xx, yy, zz);

    if( fabs(sin(winkel_Z))<0.999)
    {
        m_glWidget->lookAt(
            camPos,
            Point3D(mCamX, mCamY, mCamZ),
            Vector3D(0,0,1)
        );
    }
    else if (sin(winkel_Z)>0)
    {
        m_glWidget->lookAt(
            kamPos,
            Point3D(mCamX, mCamY, mCamZ-1),
            Vector3D(-cos(winkel_XY),-sin(winkel_XY),0)
        );
    }
    else
    {
        m_glWidget->lookAt(
            kamPos,
            Point3D(mCamX, mCamY, mCamZ+1),
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
