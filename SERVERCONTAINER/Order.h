#pragma once
#include "AllHeaders.h"
#include "Package.h"
#include "Date.h"
#include "Courier.h"
class Order {
protected:
	Package p;
	date completedOn;
	Courier deliveredBy;
public:
	Order();
	Order(Package&, date&, Courier&);
	void setPackage(Package&);
	void setDate(date&);
	void setCourier(Courier&);
	Package getPackage();
	date getDate();
	Courier getCourier();
};