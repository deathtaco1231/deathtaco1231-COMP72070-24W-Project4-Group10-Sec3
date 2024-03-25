#include "Order.h"
Order:: Order() {
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