#include "mainwindow.h"
#include <QApplication>
#include "TM.hpp"


//static Turing::Handler Debugger;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
