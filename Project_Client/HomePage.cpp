#include "HomePage.h"
#include "Package.h"
#include "Networking.h"

HomePage::HomePage(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setupClt();
    configUI();
}

HomePage::~HomePage()
{

}

void HomePage::setupClt(void) {
    QWidget::setWindowTitle(QString::fromStdString("Server"));
    setProvVector(provvect);
    ui.currentpkgID->setText(QString::fromStdString("Selected Package ID Displayed Here"));
    if (!initPkgVect()) {
        qDebug("PACKAGE VECTOR INIT FAILURE. ABORTING...");
        exit(-1);
    }
    sendCltPackages();
    for (int i = 0; i < allPkgs.size(); i++)
        allQstrPkgs.push_back(QString::fromStdString(allPkgs[i].toString()));
    for (int i = 0; i < allQstrPkgs.size(); i++)
        ui.pkgList->addItem(allQstrPkgs[i]);
    ui.infoLabel->setText(QString::fromStdString("Manager ID: " + std::to_string(currManager.getID()) + ", Name: " + currManager.getName()));
    ui.courierLabel->setText(QString::fromStdString("Courier ID: " + std::to_string(currCourier.getID()) + ", Name: " + currCourier.getName() + ", On Time: " + std::to_string(currCourier.getGoodDeliv()) + ", Late: " + std::to_string(currCourier.getLateDeliv())));
}

void HomePage::configUI(void) {
    /*QWidget::setWindowTitle(QString::fromStdString("Server"));
    setProvVector(provvect);
    ui.currentpkgID->setText(QString::fromStdString("Selected Package ID Displayed Here"));
    if (!initPkgVect()) {
        qDebug("PACKAGE VECTOR INIT FAILURE. ABORTING...");
        exit(-1);
    }
    sendCltPackages();
    for (int i = 0; i < allPkgs.size(); i++) 
        allQstrPkgs.push_back(QString::fromStdString(allPkgs[i].toString()));
    for (int i = 0; i < allQstrPkgs.size(); i++)
        ui.pkgList->addItem(allQstrPkgs[i]);  */
    ui.infoLabel->setText(QString::fromStdString("Manager ID: " + std::to_string(currManager.getID()) + ", Name: " + currManager.getName()));
    ui.courierLabel->setText(QString::fromStdString("Courier ID: " + std::to_string(currCourier.getID()) + ", Name: " + currCourier.getName() + ", On Time: " + std::to_string(currCourier.getGoodDeliv()) + ", Late: " + std::to_string(currCourier.getLateDeliv())));
    QApplication::processEvents();
    waitforClt();
}
void HomePage::on_sortstatusBtn_clicked() {
    
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
void HomePage::waitforClt(void) {
    DataPkt p = recvPacket();
    switch (p.getFlags()) {
    case DELIVFLAG: {
        DataPkt p = recvPacket();
        std::istringstream issline(p.getTBuf());
        std::string id;
        std::getline(issline, id, BODYEND);
        tmpPkg = matchbyID(std::stoi(id));
        char len[8] = { 0 };
        recvBuf(len, sizeof(len));
        long int reallen = atoi(len);
        char buf[100000] = { 0 };
        recvBuf(buf, reallen);
        FILE* fp = fopen(TMPIMG, "wb");
        fwrite(buf, reallen, 1, fp);
        fclose(fp);
        popup = new DeliveryPopup(this);
        popup->exec();
        if (isDel) {
            int index = 0;
            for (int i = 0; i < allPkgs.size(); i++)
                if (allPkgs[i].getID() == tmpPkg.getID())
                    index = i; 
            ui.pkgList->takeItem(index);
            allQstrPkgs.erase(allQstrPkgs.begin() + index);
            allPkgs.erase(allPkgs.begin() + index);
            isDel = false;
        }
        break;
    }
    }
    
}
