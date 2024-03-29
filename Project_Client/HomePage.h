#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_HomePage.h"
#include "DeliveryPopup.h"
#include "AllHeaders.h"
#include "Package.h"
#include "Manager.h"
#include "Courier.h"
#include "Order.h"
class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    HomePage(QWidget* parent = nullptr);
    ~HomePage();
    void configUI(void);
    void waitforClt(void);
    void setupClt(void);
    
private slots:
    void on_sortstatusBtn_clicked();
    void on_delPkgBtn_clicked(); 
    void on_pkgList_itemClicked(QListWidgetItem*);
private:
    Ui::HomePage ui;
    DeliveryPopup* popup;
};
std::vector<QString> allQstrPkgs;
Package currSelect;
QListWidgetItem* currItem;
void setCurrPkgSel(QListWidgetItem*);

