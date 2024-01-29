#include "PikStuff_Server_Project.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PikStuff_Server_Project w;
    w.show();
    return a.exec();
}
