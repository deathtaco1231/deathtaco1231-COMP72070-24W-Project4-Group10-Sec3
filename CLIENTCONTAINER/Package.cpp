#include "Package.h"
Package2::Package2() : Address2() {
	this->LabelImgPath = "";
	this->ID = NULL;
	this->ItemName = "UNNAMED";
	this->weight = 0;
	this->length = 0;
	this->height = 0;
	this->width = 0;
	date2 d;
	this->deliverBy = d;
}
Package2::Package2(std::string labelimg, int id, std::string itemname, double weight, double len, double width, double height, date2 d) : Address2() {
	this->LabelImgPath = labelimg;
	this->ID = id;
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
}
Package2::Package2(std::string labelimg, int id, std::string stadd, std::string city, std::string prov, std::string itemname, double weight, double len, double width, double height, date2 d) : Address2(stadd, city, prov) {
	this->LabelImgPath = labelimg;
	this->ID = id;
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
}
Package2::Package2(std::string labelimg, int id, std::string stadd, std::string city, std::string prov, int unitno, std::string itemname, double weight, double len, double width, double height, date2 d) : Address2(stadd, city, prov, unitno) {
	this->LabelImgPath = labelimg;
	this->ID = id;
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
}
void Package2::setItem(std::string itemname) {
	this->ItemName = itemname;
}
void Package2::setWeight(double a) {
	this->weight = a;
}
void Package2::setLength(double a) {
	this->length = a;
}
void Package2::setWidth(double a) {
	this->width = a;
}
void Package2::setHeight(double a) {
	this->height = a;
}
void Package2::setDeliverBy(date2 d) {
	this->deliverBy = d;
}
std::string Package2::getItem(void) {
	return this->ItemName;
}
double Package2::getWeight(void) {
	return this->weight;
}
double Package2::getLength(void) {
	return this->length;
}
double Package2::getWidth(void) {
	return this->width;
}
double Package2::getHeight(void) {
	return this->height;
}
date2 Package2::getDeliverBy(void) {
	return this->deliverBy;
}
void Package2::setID(int id) {
	this->ID = id;
}
int Package2::getID(void) {
	return this->ID;
}
std::string Package2::getImgPath(void) {
	return this->LabelImgPath;
}
std::string Package2::toString(void) {
	return std::to_string(this->ID) + "	" + ItemName + "	" + deliverBy.datetos();
}
