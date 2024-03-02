#include "Login.h"
#include "Address.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();
    return a.exec();
}
