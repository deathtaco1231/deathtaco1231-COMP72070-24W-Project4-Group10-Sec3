#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QString>
#include "ui_Server.h"

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void on_btnAdd_clicked();
    
private:
    Ui::ServerClass ui;
};
