#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Login.h"

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Project_ServerClass ui;
};
