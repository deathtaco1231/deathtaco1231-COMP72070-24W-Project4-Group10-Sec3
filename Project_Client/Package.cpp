#include "Package.h"
Package::Package() : Address() {
	this->ItemName = "UNNAMED";
	this->weight = 0;
	this->length = 0;
	this->height = 0;
	this->width = 0;
	date d;
	this->deliverBy = d;
	this->createdOn = currdate;
}
Package::Package(std::string itemname, double weight, double len, double width, double height, date d) : Address(){
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
	this->createdOn = currdate;
}
Package::Package(std::string stadd, std::string city, std::string prov, std::string itemname, double weight, double len, double width, double height, date d) : Address(stadd, city, prov) {
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
	this->createdOn = currdate;
}
Package::Package(std::string stadd, std::string city, std::string prov, int unitno, std::string itemname, double weight, double len, double width, double height, date d) : Address(stadd, city, prov, unitno) {
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
	this->createdOn = currdate;
}
void Package::setItem(std::string itemname) {
	this->ItemName = itemname;
}
void Package::setWeight(double a) {
	this->weight = a;
}
void Package::setLength(double a) {
	this->length = a;
}
void Package::setWidth(double a) {
	this->width = a;
}
void Package::setHeight(double a) {
	this->height = a;
}
void Package::setDeliverBy(date d) {
	this->deliverBy = d;
}
std::string Package::getItem(void) {
	return this->ItemName;
}
double Package::getWeight(void) {
	return this->weight;
}
double Package::getLength(void) {
	return this->length;
}
double Package::getWidth(void) {
	return this->width;
}
double Package::getHeight(void) {
	return this->height;
}
date Package::getDeliverBy(void) {
	return this->deliverBy;
}
date Package::getCreationDate(void) {
	return this->createdOn;
}