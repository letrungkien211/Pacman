#include <QtGui/QApplication>
#include "mainwindow.h"
#include <GL/glut.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    glutInit(&argc, argv);
    w.show();
    
    return a.exec();
}
