#include "maindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    maindialog main;

    main.show();

    return a.exec();
}
