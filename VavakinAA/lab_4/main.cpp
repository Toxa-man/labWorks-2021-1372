#include "mainwindow.h"
#include "expertsystem.h"
#include "tbcform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow menu;
    menu.show();
    return a.exec();
}
