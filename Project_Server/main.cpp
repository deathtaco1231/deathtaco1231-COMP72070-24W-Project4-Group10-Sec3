#include "Project_Server.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Project_Server w;
    w.show();
    return a.exec();
}
