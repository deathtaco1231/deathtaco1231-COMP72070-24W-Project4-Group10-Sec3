#include <QtCore/QCoreApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <iostream>
#include <String>
using namespace std;
void do_cpp() {
    string name;
    cout << "Enter name here: ";
    cin >> name;
    cout << "Hello " + name << "\n";
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    do_cpp();
    return a.exec();
}
