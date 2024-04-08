#include "HomePage.h"

HomePage::HomePage(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->hide();
    activateWindow();
    setWindowModality(Qt::ApplicationModal);
    this->show();
    configUI();
}

HomePage::~HomePage()
{

}

void HomePage::configUI(void) {
    QWidget::setWindowTitle(QString::fromStdString("Client"));
    ui.currentpkgID->setText(QString::fromStdString("Selected Package ID Displayed Here"));
    ui.courierLabel->setText(QString::fromStdString("Courier ID: " + std::to_string(currCourier.getID()) + ", Name: " + currCourier.getName() + ", On Time: " + std::to_string(currCourier.getGoodDeliv()) + ", Late: " + std::to_string(currCourier.getLateDeliv())));
    initPkgVect();
    for (int i = 0; i < allPkgs.size(); i++)
        allQstrPkgs.push_back(QString::fromStdString(allPkgs[i].toString()));
    for (int i = 0; i < allQstrPkgs.size(); i++)
        ui.pkgList->addItem(allQstrPkgs[i]);
}
void HomePage::setItemList(void) {
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
void HomePage::on_deliveredBtn_clicked() {
    std::string label = ui.deliveryimgline->text().toStdString();
    if (!std::filesystem::exists(label)) {
        ui.errorLabel->setText(QString::fromStdString("File not found!"));
        ui.errorLabel->setStyleSheet("QLabel { color : red; }");
    }
    else {
        if (currSelect.getID() != 0) {
            ui.errorLabel->setText("Waiting for response...");
            QApplication::processEvents();
            if (!sendDelivered(label, currSelect)) {
                this->show();
                ui.errorLabel->setText(QString::fromStdString("Server rejected delivery."));
                ui.errorLabel->setStyleSheet("QLabel { color : red; }");
            }
            else {
                ui.errorLabel->setText("");
                ui.pkgList->takeItem(ui.pkgList->row(currItem));
                int index = std::distance(allQstrPkgs.begin(), std::find(allQstrPkgs.begin(), allQstrPkgs.end(), currItem->text()));
                allQstrPkgs.erase(allQstrPkgs.begin() + index);
                allPkgs.erase(allPkgs.begin() + index);
                currSelect.setID(0);
                date currentdate = currSelect.getDeliverBy();
                if (currentdate < currdate)
                    currCourier.incLateDeliv();
                else
                    currCourier.incLateDeliv();
                ui.courierLabel->setText(QString::fromStdString("Courier ID: " + std::to_string(currCourier.getID()) + ", Name: " + currCourier.getName() + ", On Time: " + std::to_string(currCourier.getGoodDeliv()) + ", Late: " + std::to_string(currCourier.getLateDeliv())));
                ui.errorLabel->setText(QString::fromStdString("Delivery Accepted."));
            }
        }  
    }
}
void setCurrPkgSel(QListWidgetItem* item) {
    for (int i = 0; i < allQstrPkgs.size(); i++)
        if (item->text().toStdString() == allPkgs[i].toString())
            currSelect = allPkgs[i];
}
void HomePage::on_exitBtn_clicked() {
    sendFlag(EXITFLAG);
    closesocket(ClientSocket);
    WSACleanup();
    QApplication::quit();
}
void HomePage::on_requestBtn_clicked() {
    int num = std::stoi(ui.pkgnumline->text().toStdString());
    if (num > 0 && num < 10) {
        sendFlag(REQPACKAGEFLAG);
        Sleep(50);
        DataPkt s;
        s.setSeqNum(num);
        s.setHead(0, 0, 0);
        int size;
        s.setTBuf(NULL, size);
        sendToSrv(s.getTBuf(), size);
        for (int i = num; i > 0; i--) {
            DataPkt p = recvPacket();
            Package pkg = recvPackage(p);
            allPkgs.push_back(pkg);

            char len[8] = { 0 };
            recvBuf(len, sizeof(len));
            long int reallen = atoi(len);
            char* buf = new char[200000]{ 0 };
            recvBuf(buf, reallen);
            FILE* fp = fopen(pkg.getImgPath().c_str(), "wb");
            fwrite(buf, reallen, 1, fp);
            fclose(fp);
            delete[] buf;
        }
        allQstrPkgs.clear();
        ui.pkgList->clear();
        setItemList();
        ui.errorLabel->setText("Received successfully.");
    }
    else {
        ui.errorLabel->setText("Invalid entry!");
    }
}