#include "mainwindow.h"
#include <QApplication>
#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Engine engine;
    MainWindow w(&engine);
    w.show();

    return a.exec();
}
