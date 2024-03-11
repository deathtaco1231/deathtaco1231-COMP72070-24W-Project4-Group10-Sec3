#pragma once
#include "AllHeaders.h"
#include "Person.h"
class Courier : public Person {
protected:
	int GoodDeliveries, LateDeliveries;
public:
	Courier();
	Courier(int, int);
	Courier(int, int, int, int, std::string);
	void incGoodDeliv();
	void incLateDeliv();
	int getGoodDeliv();
	int getLateDeliv();
};
Courier currCourier;