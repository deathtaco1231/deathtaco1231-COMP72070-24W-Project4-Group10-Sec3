#include "Order.h"
Completed::Completed() {
	Package p;
	date d;
	Courier c;
	this->p = p;
	this->completedOn = d;
	this->deliveredBy = c;
}
Completed::Completed(Package& p, date& d, Courier& c) {
	this->p = p;
	this->completedOn = d;
	this->deliveredBy = c;
}
void Completed::setPackage(Package& p) {
	this->p = p;
}
void Completed::setDate(date& d) {
	this->completedOn = d;
}
void Completed::setCourier(Courier& c) {
	this->deliveredBy = c;
}
Package Completed::getPackage() {
	return this->p;
}
date Completed::getDate() {
	return this->completedOn;
}
Courier Completed::getCourier() {
	return this->deliveredBy;
}