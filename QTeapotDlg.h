#ifndef WINDOW_H
#define WINDOW_H

#include <QDockWidget>
#include "MyOpenGL.h"
#include "ui_dialog.h"

//UI
namespace Ui {
class OpenGLCamDialog;
}

/**
 * camera settings dialog
 * @author Tommy Hartmann
 */
class QTeapotDlg : public QDockWidget
{
    Q_OBJECT

public:

    /**
     * Constructor
     * @param parent parent Widget
     */
    explicit QTeapotDlg(MyOpenGL* openGL, QWidget* parent = 0);

    /**
     * Destructor
     */
    ~QTeapotDlg();

    /**
     * prints a line to log widget
     * @param line line that should be printed
     */
    void out(QString line);

protected:

    /** OpenGL Window */
    MyOpenGL* m_glWidget;

    /** Central Widget */
    QWidget* m_centralWidget;

private:

    /** UI Definition */
    Ui::OpenGLCamDialog *ui;

    /** zoom value */
    double m_zoom;
    /** XY position value */
    double m_posXY;
    /** z position value */
    double m_posZ;

    /** lookAt X */
    double m_camX;
    /** lookAt Y */
    double m_camY;
    /** lookAt Z */
    double m_camZ;

public slots:

    /**
     * Called if zoom has changed
     * @param zoom new zoom value
     */
    void changeZoom(int zoom);

    /**
     * Called if XY position has changed
     * @param xy new XY value
     */
    void changeXY(int xy);

    /**
     * Called if Z position has changed
     * @param z new Z value
     */
    void changeZ(int z);

    /**
     * Called if loolAt has changed
     */
    void changeLookAt();

    /**
     * Called if Camera position and/or lookAt has changed
     */
    void onCamera();

    /**
     * Called if window is closed
     */
    void onClose();

signals:

    /**
     * signals that some camera values were changed
     */
    void cameraChanged();

};

#endif
