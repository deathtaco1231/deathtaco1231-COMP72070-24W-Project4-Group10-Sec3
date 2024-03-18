#pragma once
#include "AllHeaders.h"
#include "Person.h"
class Courier2 : public Person2 {
protected:
	int GoodDeliveries, LateDeliveries;
public:
	Courier2();
	Courier2(int, int);
	Courier2(int, int, int, int, std::string);
	void incGoodDeliv();
	void incLateDeliv();
	int getGoodDeliv();
	int getLateDeliv();
};
Courier2 currCourier2;