#include "msimulator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MSimulator w;
    w.show();

    return a.exec();
}
