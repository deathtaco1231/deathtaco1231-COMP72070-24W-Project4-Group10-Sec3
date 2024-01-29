#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PikStuff_Server_Project.h"

class PikStuff_Server_Project : public QMainWindow
{
    Q_OBJECT

public:
    PikStuff_Server_Project(QWidget *parent = nullptr);
    ~PikStuff_Server_Project();

private:
    Ui::PikStuff_Server_ProjectClass ui;
};
