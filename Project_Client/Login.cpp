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

void Login::setTempUI(void) {
    if (!initSocket()) {
        qDebug("Server socket failed to initalize.");
        exit(1);
    }
    if (!connectSocket()) {
        qDebug("Connection socket failed.");
        exit(1);
    }
    setCurrentCourier();
    ui.connectingWidget->hide();
}

void Login::configUI(void) {
    QWidget::setWindowTitle(QString::fromStdString("Server Login"));
    ui.connectingWidget->setVisible(false);
    ui.usernameline->setPlaceholderText(QString("Enter username here"));
    ui.passwordline->setPlaceholderText(QString("Enter password here"));
    ui.adminline->setPlaceholderText(QString("FOR SERVER ONLY: 2FA Code"));
}

void Login::on_LoginBtn_clicked() {
    std::string uname = ui.usernameline->text().toStdString();
    std::string pword = ui.passwordline->text().toStdString();
    std::string authkey = ui.adminline->text().toStdString();
    if (authMgr(uname, pword, authkey)) {
        ui.connectingWidget->setAutoFillBackground(true);
        ui.connectingWidget->show();
        QApplication::processEvents();
        setTempUI();
        //this->close();
        this->hide();
        mainscrn = new HomePage(this);
        /*mainscrn->setWindowModality(Qt::ApplicationModal);
        this->hide();
        mainscrn->show();*/
    }
    else {
        ui.errorLabel->setText(QString::fromStdString("One or more fields not valid!"));
        ui.errorLabel->setStyleSheet("QLabel { color : red; }");
    }
}