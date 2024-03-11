#pragma once
#define COURIERFNAME ":/Data/Couriers.txt"
#include "AllHeaders.h"
#include "Person.h"
#include "Networking.h"
class Courier : public Person {
protected:
	int GoodDeliveries, LateDeliveries;
public:
	Courier();
	Courier(int, int);
	Courier(int, int, int, int, std::string, std::string, std::string);
	void incGoodDeliv();
	void incLateDeliv();
	int getGoodDeliv();
	int getLateDeliv();
};
Courier readCourier(QFile&);
bool authCourier(std::string, std::string);
void setCurrentCourier(void);
Courier currCourier;
