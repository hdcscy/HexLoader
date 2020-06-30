#include "hexloader.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HexLoader w;
    w.show();
    return a.exec();
}
