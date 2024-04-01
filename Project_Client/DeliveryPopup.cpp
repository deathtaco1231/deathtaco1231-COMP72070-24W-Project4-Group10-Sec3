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
    QPixmap demo(TMPIMG);
    ui.imglabel->setPixmap(demo);
    ui.imglabel->setScaledContents(true);
    ui.idLabel->setText(QString::fromStdString("Package ID: " + tmpPkg.getID()));
    ui.itemnameLabel->setText(QString::fromStdString("Item Name: " + tmpPkg.getItem()));
    ui.dimensionsLabel->setText(QString::fromStdString("Dimensions: Width " + std::format("{:.2f}", tmpPkg.getWidth()) + "CM, Length " + std::format("{:.2f}", tmpPkg.getLength()) + "CM, Height " + std::format("{:.2f}", tmpPkg.getHeight()) + "CM"));
    ui.weightLabel->setText(QString::fromStdString("Weight: " + std::format("{:.2f}", tmpPkg.getWeight()) + " LBS"));
    ui.toaddrLabel->setText(QString::fromStdString("To: " + tmpPkg.getstAddr()));
    ui.creationdateLabel->setText(QString::fromStdString("Created On: " + tmpPkg.getCreationDate().datetos()));
    ui.deliverdateLabel->setText(QString::fromStdString("Deliver By: " + tmpPkg.getDeliverBy().datetos()));
}
void DeliveryPopup::on_acceptBtn_clicked() {
    sendFlag(ACKFLAG);
    isDel = true;
    close();
}
void DeliveryPopup::on_declineBtn_clicked() {
    sendFlag(REJECTFLAG);
    isDel = false;
    close();
}