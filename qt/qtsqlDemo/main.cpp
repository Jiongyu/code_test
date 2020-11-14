#include "qtsqldemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication::addLibraryPath("/home/tan/software/qt5.5.1/5.5/gcc_64/plugins");
    QApplication a(argc, argv);
    qtsqlDemo w;
    w.show();

    return a.exec();
}
