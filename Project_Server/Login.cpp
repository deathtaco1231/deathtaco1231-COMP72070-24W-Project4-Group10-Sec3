#include "Login.h"

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
    if (!initSocket()) {
        qDebug("Socket failed to initalize.");
        exit(1);
    }
    ui.connectingWidget->hide();
}

void Login::configUI(void) {
    QWidget::setWindowTitle(QString::fromStdString("Client Login"));
    ui.usernameline->setPlaceholderText(QString("Enter username here"));
    ui.passwordline->setPlaceholderText(QString("Enter password here"));
}

void Login::on_LoginBtn_clicked() {
    std::string uname = ui.usernameline->text().toStdString();
    std::string pword = ui.passwordline->text().toStdString();
    sendData(uname, pword);
    if (!authCourier()) {
        ui.errorLabel->setText(QString::fromStdString("One or more fields not valid!"));
        ui.errorLabel->setStyleSheet("QLabel { color : red; }");
    }
    else {
        mainscrn = new HomePage(this);
        this->hide();
        mainscrn->show();
    }
}