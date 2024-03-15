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
    QWidget::setWindowTitle(QString::fromStdString("Client"));
  /*  ui.currentpkgID->setText(QString::fromStdString("Selected Package ID Displayed Here"));
    if (!initPkgVect()) {
        qDebug("PACKAGE VECTOR INIT FAILURE. ABORTING...");
        exit(-1);
    }
    for (int i = 0; i < allPkgs.size(); i++)
        allQstrPkgs.push_back(QString::fromStdString(allPkgs[i].toString()));
    for (int i = 0; i < allQstrPkgs.size(); i++)
        ui.pkgList->addItem(allQstrPkgs[i]);*/
}