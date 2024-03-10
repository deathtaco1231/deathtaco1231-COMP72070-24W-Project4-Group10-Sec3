#include "Login.h"
#include "Networking.h"

Login::Login(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    tempui();
    configUI();
}

Login::~Login()
{

}

void Login::tempui(void) {
    ui.connectingWidget->setAutoFillBackground(true);
    ui.connectingWidget->show();
   /* if (!initSocket()) {
        qDebug("Socket failed to initalize.");
        exit(1);
    }*/
    ui.connectingWidget->hide();
}

void Login::configUI(void) {
    ui.usernameline->setPlaceholderText(QString("Enter username here"));
    ui.passwordline->setPlaceholderText(QString("Enter password here"));
}

void Login::on_LoginBtn_clicked() {
    std::string uname = ui.usernameline->text().toStdString();
    std::string pword = ui.passwordline->text().toStdString();
    mainscrn = new HomePage(this);
    mainscrn->show();
    this->hide();
}