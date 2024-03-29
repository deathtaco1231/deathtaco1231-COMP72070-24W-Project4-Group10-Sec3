#include "Package.h"
Package::Package() : Address() {
	this->LabelImgPath = "";
	this->ID = NULL;
	this->ItemName = "UNNAMED";
	this->weight = 0;
	this->length = 0;
	this->height = 0;
	this->width = 0;
	date d;
	this->deliverBy = d;
}
Package::Package(std::string labelimg, int id, std::string itemname, double weight, double len, double width, double height, date d) : Address() {
	this->LabelImgPath = labelimg;
	this->ID = id;
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
}
Package::Package(std::string labelimg, int id, std::string stadd, std::string city, std::string prov, std::string itemname, double weight, double len, double width, double height, date d) : Address(stadd, city, prov) {
	this->LabelImgPath = labelimg;
	this->ID = id;
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
}
Package::Package(std::string labelimg, int id, std::string stadd, std::string city, std::string prov, int unitno, std::string itemname, double weight, double len, double width, double height, date d) : Address(stadd, city, prov, unitno) {
	this->LabelImgPath = labelimg;
	this->ID = id;
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
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
void Package::setID(int id) {
	this->ID = id;
}
int Package::getID(void) {
	return this->ID;
}
std::string Package::getImgPath(void) {
	return this->LabelImgPath;
}
std::string Package::toString(void) {
	return std::to_string(this->ID) + "	" + ItemName + "	" + deliverBy.datetos();
}
