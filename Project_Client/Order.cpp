#include "Order.h"
Order::Order() {
	Package p;
	date d;
	Courier c;
	this->p = p;
	this->completedOn = d;
	this->deliveredBy = c;
}
Order::Order(Package& p, date& d, Courier& c) {
	this->p = p;
	this->completedOn = d;
	this->deliveredBy = c;
}
void Order::setPackage(Package& p) {
	this->p = p;
}
void Order::setDate(date& d) {
	this->completedOn = d;
}
void Order::setCourier(Courier& c) {
	this->deliveredBy = c;
}
Package Order::getPackage() {
	return this->p;
}
date Order::getDate() {
	return this->completedOn;
}
Courier Order::getCourier() {
	return this->deliveredBy;
}
void writeOrderToFile(Order& o) {
	time_t now = time(0);
	char dt[100] = { 0 };
	ctime_s(dt, sizeof(dt), &now);
	std::ofstream out(ORDERFNAME, std::ios::app);
	std::string late;
	date d1 = o.getPackage().getDeliverBy();
	date d2 = o.getDate();
	if (d1 < d2) {
		late = "Yes";
		currCourier.incLateDeliv();
	}
	else {
		late = "No";
		currCourier.incGoodDeliv();
	}
	out << "Order Completed At: " << dt << std::endl;
	out << "Package ID: " << o.getPackage().getID() << "	" << "Item Name: " << o.getPackage().getItem() << std::endl;
	out << "Weight: " << std::format("{:.2f}", o.getPackage().getWeight()) << "LBS" << "	" << "Length: " << std::format("{:.2f}", o.getPackage().getLength()) << "CM" << "	" << "Width: " << std::format("{:.2f}", o.getPackage().getWidth()) << "CM" << "	" << "Height: " << std::format("{:.2f}", o.getPackage().getHeight()) << "CM" << std::endl;
	out << "Created on: " << o.getPackage().getCreationDate().datetos() << "	" << "Delivery Deadline: " << o.getPackage().getDeliverBy().datetos() << "	" << "Actual Delivery Date: " << o.getDate().datetos() << std::endl;
	out << "Late? --> " << late << std::endl;
	out << "Delivered by courier: " << o.getCourier().getName() << "	" << "ID: " << o.getCourier().getID() << "\n\n" << std::endl;
	out.close();
}