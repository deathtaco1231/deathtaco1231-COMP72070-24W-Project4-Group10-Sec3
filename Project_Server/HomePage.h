#pragma once
#include "AllHeaders.h"
#include <QtWidgets/QMainWindow>
#include "ui_HomePage.h"
#include "Package.h"
class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    HomePage(QWidget* parent = nullptr);
    ~HomePage();
    void configUI(void);
private slots:
    void on_sortstatusBtn_clicked();
    void on_delPkgBtn_clicked();
    
private:
    Ui::MainWindow ui;
};
std::vector<QString> allQstrPkgs;
Package currSelect;
