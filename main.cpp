#include <QApplication>
#include "UdpWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UdpWidget w;
    w.setWindowTitle("STM32 UDP Tool");
    w.resize(800, 600);
    w.show();
    return a.exec();
}

