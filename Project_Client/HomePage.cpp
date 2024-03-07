#include "HomePage.h"
#include "Package.h"

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
    setProvVector(provvect);
    ui.currentpkgID->setText(QString::fromStdString("Selected Package ID Displayed Here"));
    if (!initPkgVect()) {
        qDebug("PACKAGE VECTOR INIT FAILURE. ABORTING...");
        exit(-1);
    }
    for (int i = 0; i < allPkgs.size(); i++) 
        allQstrPkgs.push_back(QString::fromStdString(allPkgs[i].toString()));
    for (int i = 0; i < allQstrPkgs.size(); i++)
        ui.pkgList->addItem(allQstrPkgs[i]);  
}
void HomePage::on_sortstatusBtn_clicked() {
    popup = new DeliveryPopup(this);
    popup->show();
}
void HomePage::on_delPkgBtn_clicked() {
    if (ui.pkgList->takeItem(ui.pkgList->row(currItem)) != nullptr) {
        int index = std::distance(allQstrPkgs.begin(), std::find(allQstrPkgs.begin(), allQstrPkgs.end(), currItem->text()));
        allQstrPkgs.erase(allQstrPkgs.begin() + index);
        allPkgs.erase(allPkgs.begin() + index);
    }
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
    ui.creationdateLabel->setText(QString::fromStdString("Created On: " + currSelect.getCreationDate().datetos()));
    ui.deliverdateLabel->setText(QString::fromStdString("Deliver By: " + currSelect.getDeliverBy().datetos()));
}
void setCurrPkgSel(QListWidgetItem* item) {
    for (int i = 0; i < allQstrPkgs.size(); i++) 
        if (item->text().toStdString() == allPkgs[i].toString())
            currSelect = allPkgs[i];
}