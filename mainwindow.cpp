#include "stdafx.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_openGLWidget(0)
    , m_dialog(0)
{
    ui->setupUi(this);

    if(!ui->centralWidget->layout())
    {
        ui->centralWidget->setLayout(new QHBoxLayout);
    }

    //Teapot
    CGraphic g = CGraphic();

    //Init glWindow
    m_openGLWidget = new MyOpenGL();
    m_openGLWidget->InitOpenGL("QTeapot",0,500,0,500);
    m_openGLWidget->show();


    //Connect graphic and glWindow
    m_openGLWidget->setGrafik(&g);
    g.Init();


    //Create Camera Dialog
    m_dialog = new QTeapotDlg(m_openGLWidget);

    ui->centralWidget->layout()->addWidget(m_openGLWidget);
    this->addDockWidget(Qt::RightDockWidgetArea, m_dialog);


    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}
