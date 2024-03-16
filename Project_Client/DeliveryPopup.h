#pragma once
#include "AllHeaders.h"
#include <QtWidgets/QDialog>
#include "ui_DeliveryPopup.h"
#include "Package.h"
#include "Networking.h"

class DeliveryPopup : public QDialog {

	Q_OBJECT;
	
public:
	DeliveryPopup(QWidget* parent = nullptr);
	~DeliveryPopup();
	void configUI(void);
private slots:
	void on_acceptBtn_clicked();
	void on_declineBtn_clicked();

private:
	Ui::Dialog ui;

};