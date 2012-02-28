#include <QtGui/QApplication>
#include <QDesktopWidget>
#include "QTeapotDlg.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTeapotDlg window;
    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();
    return app.exec();
}
