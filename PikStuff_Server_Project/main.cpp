#include "PikStuff_Server_Project.h"
#include <QtWidgets/QApplication>
#include <QCoreApplication>
#include <QTextStream>
#include <qdebug.h>
#include <String>
#include <iostream>
using namespace std;
/*void do_qt() {
    QTextStream qin(stdin);
    QTextStream qout(stdout);

    qout() << "Please enter your name:";
    qout.flush();
    QString name = qin.readLine();
    qout << "Hello " << "\n";
    qout.flush();
}*/
void do_cpp() {
    string name;
    cout << "Enter name here: ";
    cin >> name;
    cout << "Hello " + name << "\n";
}
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    //PikStuff_Server_Project w;
    //w.show();
   // qDebug() << "balls" << "\n";
    
    do_cpp();
    return a.exec();
}
