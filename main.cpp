#include "stegsolve.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Stegsolve w;
    w.show();

    return a.exec();
}
