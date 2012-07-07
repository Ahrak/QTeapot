#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QTeapotDlg.h"
#include "MyOpenGL.h"

namespace Ui {
class MainWindow;
}


/**
 * MainWindow
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * Constructor
     * @param parent parent widget
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * Destructor
     */
    ~MainWindow();

private:

    /** Ui definition */
    Ui::MainWindow *ui;
    /** OpenGL Widget */
    MyOpenGL* m_openGLWidget;
    /** Camera dialog */
    QTeapotDlg* m_dialog;
};

#endif // MAINWINDOW_H
