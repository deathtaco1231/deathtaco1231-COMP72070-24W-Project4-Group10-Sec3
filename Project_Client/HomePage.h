#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HomePage.h"
#include "DeliveryPopup.h"

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    HomePage(QWidget* parent = nullptr);
    ~HomePage();
    void configUI(void);
private slots:
    void on_sortstatusBtn_clicked();
private:
    Ui::HomePage ui;
    DeliveryPopup* popup;
};
