#include "HomePage.h"
#include "Package.h"
#include "Networking.h"

HomePage::HomePage(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->hide();
    activateWindow();
    this->setWindowModality(Qt::ApplicationModal);
    this->show();
    setupClt();
    configUI();
}

HomePage::~HomePage()
{

}

void HomePage::setupClt(void) {
    QWidget::setWindowTitle(QString::fromStdString("Server"));
    setCourierVect();
    setProvVector(provvect);
    ui.currentpkgID->setText(QString::fromStdString("Selected Package ID Displayed Here"));
    if (!initPkgVect()) {
        qDebug("PACKAGE VECTOR INIT FAILURE. ABORTING...");
        exit(-1);
    }
    sendCltPackages();
    setItemList();
    ui.infoLabel->setText(QString::fromStdString("Manager ID: " + std::to_string(currManager.getID()) + ", Name: " + currManager.getName()));
    ui.courierLabel->setText(QString::fromStdString("Courier ID: " + std::to_string(currCourier.getID()) + ", Name: " + currCourier.getName() + ", On Time: " + std::to_string(currCourier.getGoodDeliv()) + ", Late: " + std::to_string(currCourier.getLateDeliv())));
}
void HomePage::setItemList(void) {
    for (int i = 0; i < allPkgs.size(); i++)
        allQstrPkgs.push_back(QString::fromStdString(allPkgs[i].toString()));
    for (int i = 0; i < allQstrPkgs.size(); i++)
        ui.pkgList->addItem(allQstrPkgs[i]);
}
void HomePage::configUI(void) {
    ui.infoLabel->setText(QString::fromStdString("Manager ID: " + std::to_string(currManager.getID()) + ", Name: " + currManager.getName()));
    ui.courierLabel->setText(QString::fromStdString("Courier ID: " + std::to_string(currCourier.getID()) + ", Name: " + currCourier.getName() + ", On Time: " + std::to_string(currCourier.getGoodDeliv()) + ", Late: " + std::to_string(currCourier.getLateDeliv())));
    QApplication::processEvents();
    waitforClt();
}
void HomePage::on_sortstatusBtn_clicked() {
    
}
void HomePage::on_sendPkgBtn_clicked() {
    int size;
    DataPkt p = fmtPkg(currSelect, size);
    setVectPkgAssigned(currSelect);
    sendToClt(p.getTBuf(), size);
    Sleep(100);
    long int len = GetFileSize(currSelect.getImgPath().c_str());
    FILE* in;
    fopen_s(&in, currSelect.getImgPath().c_str(), "rb");
    char* buf = new char[200000] { 0 };
    fread(buf, 1, len, in);
    fclose(in);
    char strlen[8] = { 0 };
    _itoa_s(len, strlen, 10);
    Sleep(100);
    sendToClt(strlen, sizeof(strlen));
    Sleep(150);
    sendToClt(buf, len);
    delete[] buf;
    ui.remainingLabel->setText(QString::fromStdString("Remaining: " + std::to_string(--pkgCount)));
    allQstrPkgs.clear();
    ui.pkgList->clear();
    setItemList();
    QApplication::processEvents();
    if (pkgCount == 0)
        waitforClt();
    
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


    date currentDate;
    setcurrdate();

    for (int i = 0; i < allQstrPkgs.size(); i++) {
        if (item->text().toStdString() == allPkgs[i].toString()) {
            currentDate = allPkgs[i].getDeliverBy();
            break;
        }
    }

    // Highlight in red if the delivery date is before the current date
    if (currentDate < currdate) {
        ui.deliverdateLabel->setStyleSheet("QLabel { color: red; }");
    }
    else {
        ui.deliverdateLabel->setStyleSheet("");
    }

    
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
        char* buf = new char[200000]{ 0 };
        recvBuf(buf, reallen);
        FILE* fp = fopen(TMPIMG, "wb");
        fwrite(buf, reallen, 1, fp);
        fclose(fp);
        setFocus();
        popup = new DeliveryPopup(this);
        popup->exec();
        if (isDel) {
            int index = 0;
            for (int i = 0; i < allPkgs.size(); i++)
                if (allPkgs[i].getID() == tmpPkg.getID())
                    index = i; 
            Order newOrder(allPkgs[index], currdate, currCourier);
            writeOrderToFile(newOrder);
            ui.pkgList->takeItem(index);
            allQstrPkgs.erase(allQstrPkgs.begin() + index);
            allPkgs.erase(allPkgs.begin() + index);
            isDel = false;
        }
        delete[] buf;
        configUI();
        break;
    }
    case REQPACKAGEFLAG: {
        DataPkt p = recvPacket();
        pkgCount = p.getSeqNum();
        this->raise(); // TEST
        ui.remainingLabel->setText(QString::fromStdString("Remaining: " + std::to_string(pkgCount)));
        break;
    }
    case EXITFLAG:
    {
        writeAllCouriers();
        writeAllPackages();
        closesocket(ServerSocket);
        closesocket(ConnectionSocket);
        WSACleanup();
        QApplication::quit();
        break;
    }
    }
    
}
