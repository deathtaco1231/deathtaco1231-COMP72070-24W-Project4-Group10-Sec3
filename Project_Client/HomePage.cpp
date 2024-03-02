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
    date d(15, 10, 2024);
    Package p1("", 1, "Tiny Shoes For Alyssas Mom", 4.2, 5.68, 2.93, 4.5, d);
    Package p2("", 2, "Shoes", 4.2, 5.68, 2.93, 4.5, d);
    Package p3("", 3, "Shoes", 4.2, 5.68, 2.93, 4.5, d);
    Package p4("", 4, "Shoes", 4.2, 5.68, 2.93, 4.5, d);
    allPkgs.push_back(p1);
    allPkgs.push_back(p2);
    allPkgs.push_back(p3);
    allPkgs.push_back(p4);
    for (int i = 0; i < allPkgs.size(); i++) 
        allQstrPkgs.push_back(QString::fromStdString(allPkgs[i].toString()));
    for (int i = 0; i < allQstrPkgs.size(); i++)
        ui.pkgList->addItem(allQstrPkgs[i]);

    QPixmap demo(":/Images/Label.jpg");
    ui.label_6->setPixmap(demo);
    ui.label_6->setScaledContents(true);
    
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
}
//ui.pkgList->takeItem(ui.pkgList->row(item)); - FOR DELETING SELECTED ITEM
void setCurrPkgSel(QListWidgetItem* item) {
    for (int i = 0; i < allQstrPkgs.size(); i++) 
        if (item->text().toStdString() == allPkgs[i].toString())
            currSelect = allPkgs[i];
}