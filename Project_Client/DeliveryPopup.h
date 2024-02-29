#pragma once
#include "AllHeaders.h"
#include <QtWidgets/QDialog>
#include "ui_DeliveryPopup.h"

class DeliveryPopup : public QDialog {

	Q_OBJECT;
	std::string ImgName = "C:/Users/dankp/Downloads/DeliveredPackage.jpg";
public:
	DeliveryPopup(QWidget* parent = nullptr);
	~DeliveryPopup();
	void configUI(void);
private slots:

private:
	Ui::Dialog ui;

};