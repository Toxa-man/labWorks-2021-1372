#include "minesweeper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Minesweeper w;
    w.move(300,300);
    w.setWindowTitle("Minesweeper");
    w.show();
    return a.exec();
}
