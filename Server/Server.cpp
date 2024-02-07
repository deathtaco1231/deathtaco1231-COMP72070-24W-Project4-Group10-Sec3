#include "Server.h"

Server::Server(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

Server::~Server()
{
    // delete ui;
}

void Server::on_btnAdd_clicked() {
    int first, second, third;
    first = ui.txtFirstNum->text().toInt();
    second = ui.txtSecondNum->text().toInt();
    third = first + second;
    ui.txtResultNum->setText(QString::number(third));
}