#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Login.h"
#include "HomePage.h"

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget* parent = nullptr);
    ~Login();
    void configUI(void);
    void tempui(void);
private slots:
    void on_LoginBtn_clicked();

private:
    Ui::Project_ServerClass ui;
    HomePage* mainscrn;
};
