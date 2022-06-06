#include "translator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Translator w;
    w.show();
    return a.exec();
}
