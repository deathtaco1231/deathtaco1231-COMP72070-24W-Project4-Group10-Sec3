#pragma once
#include "AllHeaders.h"
#include <QtWidgets/QDialog>
#include "ui_DeliveryPopup.h"

class DeliveryPopup : public QDialog {

	Q_OBJECT

public:
	DeliveryPopup(QWidget* parent = nullptr);
	~DeliveryPopup();
	void configUI(void);
private slots:

private:
	Ui::Dialog ui;

};