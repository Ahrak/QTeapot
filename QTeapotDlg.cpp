#include <QtGui>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <math.h>
#include <iostream>
#include "QTeapotDlg.h"

QTeapotDlg::QTeapotDlg()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* layout = new QVBoxLayout;
    mainLayout->addLayout(layout);

    //init vars
    mZoom = 10;
    mPosXY = 45;
    mPosZ = 45;

    mCamX = 0;
    mCamY = 0;
    mCamZ = 0;

    //size of control window
    this->setFixedSize(250,400);
    this->setWindowTitle("Camera Control");

    //Position
    QHBoxLayout* posLayout = new QHBoxLayout;
    QLabel* lblPX = new QLabel("X");
    editPX = new QLineEdit(QString("%1").arg(mCamX));
    QLabel* lblPY = new QLabel("Y");
    editPY = new QLineEdit(QString("%1").arg(mCamY));
    QLabel* lblPZ = new QLabel("Z");
    editPZ = new QLineEdit(QString("%1").arg(mCamZ));
    QPushButton* btnPos = new QPushButton("Set");
    posLayout->addWidget(lblPX);
    posLayout->addWidget(editPX);
    posLayout->addWidget(lblPY);
    posLayout->addWidget(editPY);
    posLayout->addWidget(lblPZ);
    posLayout->addWidget(editPZ);
    layout->addLayout(posLayout);
    layout->addWidget(btnPos);

    //Zoom
    QSlider* sliderZoom = new QSlider(Qt::Horizontal);
    QHBoxLayout* zoomLayout = new QHBoxLayout;
    QLabel* lblZoom = new QLabel("Zoom");
    valueZoom = new QLabel(QString("%1").arg(mZoom));
    sliderZoom->setRange(0,30);
    sliderZoom->setTickInterval(1);
    sliderZoom->setSliderPosition(mZoom);
    layout->addLayout(zoomLayout);
    zoomLayout->addWidget(lblZoom);
    zoomLayout->addWidget(valueZoom);
    layout->addWidget(sliderZoom);

    //XY
    QSlider* sliderXY = new QSlider(Qt::Horizontal);
    QHBoxLayout* xyLayout = new QHBoxLayout;
    QLabel* lblXY = new QLabel("XY");
    valueXY = new QLabel(QString("%1").arg(mPosXY));
    sliderXY->setRange(0,360);
    sliderXY->setTickInterval(9);
    sliderXY->setSliderPosition(mPosXY);
    layout->addLayout(xyLayout);
    xyLayout->addWidget(lblXY);
    xyLayout->addWidget(valueXY);
    layout->addWidget(sliderXY);

    //Z
    QSlider* sliderZ = new QSlider(Qt::Vertical);
    QVBoxLayout* zLayout = new QVBoxLayout;
    QLabel* lblZ = new QLabel("Z");
    valueZ = new QLabel(QString("%1").arg(mPosZ));
    sliderZ->setRange(-90,90);
    sliderZ->setTickInterval(9);
    sliderZ->setSliderPosition(mPosZ);
    mainLayout->addLayout(zLayout);
    zLayout->addWidget(lblZ);
    zLayout->addWidget(sliderZ);
    zLayout->addWidget(valueZ);


    //output
    output = new QTextEdit("");
    layout->addWidget(output);


    //Signals
    QObject::connect(sliderZoom, SIGNAL( valueChanged(int)), this, SLOT( changeZoom(int) ));
    QObject::connect(sliderXY, SIGNAL( valueChanged(int)), this, SLOT( changeXY(int) ));
    QObject::connect(sliderZ, SIGNAL( valueChanged(int)), this, SLOT( changeZ(int) ));
    QObject::connect(btnPos, SIGNAL( pressed()), this, SLOT( changeLookAt() ));
    QObject::connect(this, SIGNAL( cameraChanged()), this, SLOT( onCamera() ));
    //QObject::connect(this, SIGNAL( destroyed()), this, SLOT(onClose()));
    //QObject::connect(glWidget, SIGNAL( destroyed()), this, SLOT(onClose()));


    //----------OPENGL WINDOW----------------
    glWidget = new MyOpenGL;
    glWidget->show();
    glWidget->InitOpenGL("QTeapot",0,500,0,500);
    glWidget->setGrafik(&mGrafik);
    mGrafik.Init();

    this->move(520,0);

    emit cameraChanged();

    glWidget->ortho(-mZoom, mZoom, -mZoom, mZoom, -100000, 100000);
}


void QTeapotDlg::changeZoom(int zoom)
{
    this->mZoom = zoom;
    valueZoom->setText(QString("%1").arg(zoom));
    glWidget->ortho(-mZoom, mZoom, -mZoom, mZoom, -100000, 100000);
    emit cameraChanged();
}

void QTeapotDlg::changeXY(int xy)
{
    mPosXY = xy;
    valueXY->setText(QString("%1").arg(xy));
    emit cameraChanged();
}

void QTeapotDlg::changeZ(int z)
{
    mPosZ = z;
    valueZ->setText(QString("%1").arg(z));
    emit cameraChanged();
}


void QTeapotDlg::changeLookAt()
{
    mCamX = editPX->text().toFloat();
    mCamY = editPY->text().toFloat();
    mCamZ = editPZ->text().toFloat();

    out(QString("New lookAt point: (%1, %2, %3)")
        .arg(mCamX).arg(mCamY).arg(mCamZ));

    emit cameraChanged();
}


void QTeapotDlg::onClose()
{
    this->close();
    glWidget->close();
}

void QTeapotDlg::onCamera() {

    Point3D kamPos;
    float winkel_XY, winkel_Z;
    float xx, yy, zz;
    //Winkel ins Bogenmaß umrechnen
    winkel_XY = mPosXY/180 * M_PI;
    winkel_Z = mPosZ/180 * M_PI;
    //Kamerapositionen
    xx = mCamX + cos(winkel_Z) * cos(winkel_XY);
    yy = mCamY + cos(winkel_Z) * sin(winkel_XY);
    zz = mCamZ + sin(winkel_Z);

    kamPos.set(xx, yy, zz);

    if( fabs(sin(winkel_Z))<0.999) {
        glWidget->lookAt(
            kamPos,
            Point3D(mCamX, mCamY, mCamZ),
            Vector3D(0,0,1)
        );
    }
    else if (sin(winkel_Z)>0)
    {
        glWidget->lookAt(
            kamPos,
            Point3D(mCamX, mCamY, mCamZ-1),
            Vector3D(-cos(winkel_XY),-sin(winkel_XY),0)
        );
    }
    else
    {
        glWidget->lookAt(
            kamPos,
            Point3D(mCamX, mCamY, mCamZ+1),
            Vector3D(cos(winkel_XY),sin(winkel_XY),0)
        );
    }

    glWidget->invalidate();
}


void QTeapotDlg::out(QString line)
{
    output->append(line);
}
