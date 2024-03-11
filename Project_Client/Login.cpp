#include "Login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setcurrdate();
    configUI();
}

Login::~Login()
{
    
}

void Login::configUI(void) {
    ui.usernameline->setPlaceholderText(QString("Enter username here"));
    ui.passwordline->setPlaceholderText(QString("Enter password here"));
    ui.adminline->setPlaceholderText(QString("FOR SERVER ONLY: 2FA Code"));
}

void Login::on_LoginBtn_clicked() {
    std::string uname = ui.usernameline->text().toStdString();
    std::string pword = ui.passwordline->text().toStdString();
    std::string authkey = ui.adminline->text().toStdString();
    if (authMgr(uname, pword, authkey)) {
        mainscrn = new HomePage(this);
        mainscrn->show();
        this->hide();
    }
    else {
        ui.errorLabel->setText(QString::fromStdString("One or more fields not valid!"));
        ui.errorLabel->setStyleSheet("QLabel { color : red; }");
    }
}