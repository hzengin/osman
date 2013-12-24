#include <QtGui/QApplication>
#include "osman.h"
#include "./fluid/fluid_menu.h"
#include <QDir>
#include <QFile>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    osman w;
    fluid_menu menu(&w);
    menu.showFullScreen();
    return a.exec();
}
