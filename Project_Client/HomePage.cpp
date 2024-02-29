#include "HomePage.h"
#include "DataPacket.h"
#include "Address.h"

HomePage::HomePage(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    configUI();
}

HomePage::~HomePage()
{

}

void HomePage::configUI(void) {
    std::string addr = "200 Old Carriage Drive";
    Address *a = new Address(addr, addr, addr, 0);
    ui.listWidget->addItem(QString::fromStdString("Package Info Per Line Here"));
    QPixmap demo("C:/Users/dankp/Downloads/Label.jpg");
    ui.label_6->setPixmap(demo);
    ui.label_6->setScaledContents(true);
    
}

void HomePage::on_sortstatusBtn_clicked() {
    popup = new DeliveryPopup(this);
    popup->show();
}