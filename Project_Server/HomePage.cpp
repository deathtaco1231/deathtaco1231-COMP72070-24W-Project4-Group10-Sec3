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
    ui.currentpkgID->setText(QString::fromStdString("Selected Package ID Displayed Here"));
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
                currCourier.incGoodDeliv();
                ui.courierLabel->setText(QString::fromStdString("Courier ID: " + std::to_string(currCourier.getID()) + ", Name: " + currCourier.getName() + ", On Time: " + std::to_string(currCourier.getGoodDeliv()) + ", Late: " + std::to_string(currCourier.getLateDeliv())));
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