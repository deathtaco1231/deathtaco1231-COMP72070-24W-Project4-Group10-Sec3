#include "Login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    configUI();
}

Login::~Login()
{
    
}

void Login::configUI(void) {
    ui.usernameline->setPlaceholderText(QString("Enter username here"));
    ui.passwordline->setPlaceholderText(QString("Enter password here"));
}

void Login::on_LoginBtn_clicked() {
    mainscrn = new HomePage(this);
    mainscrn->show();
}