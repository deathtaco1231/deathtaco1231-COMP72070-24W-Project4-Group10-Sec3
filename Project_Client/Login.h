#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Project_Client.h"

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Project_ClientClass ui;
};

void configUI(void);