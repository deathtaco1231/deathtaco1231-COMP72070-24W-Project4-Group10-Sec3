#include "HomePage.h"
#include "DataPacket.h"

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
    ui.listWidget->addItem(QString::fromStdString(a->getCity()) + QString::fromStdString(a->getProvince()));

}