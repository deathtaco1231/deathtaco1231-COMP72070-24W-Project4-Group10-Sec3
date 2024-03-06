#include "DeliveryPopup.h"

DeliveryPopup::DeliveryPopup(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    configUI();
}

DeliveryPopup::~DeliveryPopup()
{

}

void DeliveryPopup::configUI(void) {
    QPixmap demo(":/Images/DeliveredPackage.jpg");
    ui.imglabel->setPixmap(demo);
    ui.imglabel->setScaledContents(true);
}