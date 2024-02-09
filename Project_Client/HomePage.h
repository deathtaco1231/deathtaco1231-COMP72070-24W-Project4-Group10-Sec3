#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HomePage.h"

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    HomePage(QWidget* parent = nullptr);
    ~HomePage();
    void configUI(void);
private slots:

private:
    Ui::HomePage ui;
};
