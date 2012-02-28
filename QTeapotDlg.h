#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include "Grafik.h"
#include "MyOpenGL.h"

class QTeapotDlg : public QWidget
{
    Q_OBJECT

public:
    QTeapotDlg();
    void out(QString line);

protected:
    //openGL Window
    MyOpenGL* glWidget;

private:

    CGrafik mGrafik;

    //vars
    float mZoom;
    float mPosXY;
    float mPosZ;

    float mCamX;
    float mCamY;
    float mCamZ;

    //valueLabels
    QLabel* valueZoom;
    QLabel* valueXY;
    QLabel* valueZ;
    QLineEdit * editPX;
    QLineEdit * editPY;
    QLineEdit * editPZ;

    QTextEdit * output;

public slots:
    void changeZoom(int zoom);
    void changeXY(int xy);
    void changeZ(int z);
    void changeLookAt();
    void onCamera();
    void onClose();

signals:
    void cameraChanged();


};

#endif
