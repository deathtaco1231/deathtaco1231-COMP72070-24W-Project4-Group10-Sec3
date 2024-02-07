#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Project_Server.h"

class Project_Server : public QMainWindow
{
    Q_OBJECT

public:
    Project_Server(QWidget *parent = nullptr);
    ~Project_Server();

private:
    Ui::Project_ServerClass ui;
};
