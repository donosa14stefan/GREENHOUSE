#include <QApplication>
#include <QDesktopWidget>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Force using offscreen rendering if X11 is not available
    qputenv("QT_QPA_PLATFORM", "offscreen");
    
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
