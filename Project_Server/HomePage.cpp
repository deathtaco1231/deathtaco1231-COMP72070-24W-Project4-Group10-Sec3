#include "HomePage.h"

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
    QWidget::setWindowTitle(QString::fromStdString("Client"));
    ui.courierLabel->setText(QString::fromStdString("Courier ID: " + std::to_string(currCourier.getID()) + ", Name: " + currCourier.getName() + ", On Time: " + std::to_string(currCourier.getGoodDeliv()) + ", Late: " + std::to_string(currCourier.getLateDeliv())));
    initPkgVect();
    for (int i = 0; i < allPkgs.size(); i++)
        allQstrPkgs.push_back(QString::fromStdString(allPkgs[i].toString()));
    for (int i = 0; i < allQstrPkgs.size(); i++)
        ui.pkgList->addItem(allQstrPkgs[i]);
}
void HomePage::on_pkgList_itemClicked(QListWidgetItem* item) {
    setCurrPkgSel(item);
    currItem = item;
    ui.currentpkgID->setText(QString::fromStdString("Current Selection: Package #" + std::to_string(currSelect.getID())));
    QPixmap lol(QString::fromStdString(currSelect.getImgPath()));
    ui.label_6->setPixmap(lol);
    ui.label_6->setScaledContents(true);
    ui.itemnameLabel->setText(QString::fromStdString("Item Name: " + currSelect.getItem()));
    ui.dimensionsLabel->setText(QString::fromStdString("Dimensions: Width " + std::format("{:.2f}", currSelect.getWidth()) + "CM, Length " + std::format("{:.2f}", currSelect.getLength()) + "CM, Height " + std::format("{:.2f}", currSelect.getHeight()) + "CM"));
    ui.weightLabel->setText(QString::fromStdString("Weight: " + std::format("{:.2f}", currSelect.getWeight()) + " LBS"));
    ui.toaddrLabel->setText(QString::fromStdString("To: " + currSelect.getstAddr()));
    ui.deliverdateLabel->setText(QString::fromStdString("Deliver By: " + currSelect.getDeliverBy().datetos()));
}
void setCurrPkgSel(QListWidgetItem* item) {
    for (int i = 0; i < allQstrPkgs.size(); i++)
        if (item->text().toStdString() == allPkgs[i].toString())
            currSelect = allPkgs[i];
}