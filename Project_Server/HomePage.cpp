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
    ui.exitBtn->setStyleSheet("QPushButton {background-color: #A3C1DA; border:  none}");
    ui.courierLabel->setText(QString::fromStdString("Courier ID: " + std::to_string(currCourier.getID()) + ", Name: " + currCourier.getName() + ", On Time: " + std::to_string(currCourier.getGoodDeliv()) + ", Late: " + std::to_string(currCourier.getLateDeliv())));
    ui.currentpkgID->setText(QString::fromStdString("Selected Package ID Displayed Here"));
    initPkgVect();

       
    for (int i = 0; i < allPkgs.size(); i++)
        allQstrPkgs.push_back(QString::fromStdString(allPkgs[i].toString()));
    for (int i = 0; i < allQstrPkgs.size(); i++)
        ui.pkgList->addItem(allQstrPkgs[i]);
}