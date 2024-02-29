#include "Package.h"
Package::Package() : Address() {
	this->ID = NULL;
	this->ItemName = "UNNAMED";
	this->weight = 0;
	this->length = 0;
	this->height = 0;
	this->width = 0;
	date d;
	this->deliverBy = d;
	this->createdOn = currdate;
	this->isAssigned = false;
}
Package::Package(int id, std::string itemname, double weight, double len, double width, double height, date d) : Address(){
	this->ID = id;
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
	this->createdOn = currdate;
	this->isAssigned = false;
}
Package::Package(int id, std::string stadd, std::string city, std::string prov, std::string itemname, double weight, double len, double width, double height, date d) : Address(stadd, city, prov) {
	this->ID = id;
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
	this->createdOn = currdate;
	this->isAssigned = false;
}
Package::Package(int id, std::string stadd, std::string city, std::string prov, int unitno, std::string itemname, double weight, double len, double width, double height, date d) : Address(stadd, city, prov, unitno) {
	this->ID = id;
	this->ItemName = itemname;
	this->weight = weight;
	this->length = len;
	this->width = width;
	this->height = height;
	this->deliverBy = d;
	this->createdOn = currdate;
	this->isAssigned = false;
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
void Package::setID(int id) {
	this->ID = id;
}
int Package::getID(void) {
	return this->ID;
}
void Package::setAssigned(void) {
	isAssigned = true;
}
bool Package::checkifassigned(void) {
	return isAssigned;
}

bool initPkgVect(void) {
	std::ifstream in;
	in.open(PKGFNAME);
	if (!in.is_open())
		return false;
	while (!in.eof()) {
		Package p = readPkg(in);
		allPkgs.push_back(p);
	}
	return true;
}
Package readPkg(std::ifstream& in) {
	std::string line, id, stadd, city, prov, itemname, weight, length, width, height, day, month, year, isAssigned;
	std::getline(in, line);
	std::istringstream isline(line);
	std::getline(isline, id, DELIM);
	std::getline(isline, stadd, DELIM);
	std::getline(isline, city, DELIM);
	std::getline(isline, prov, DELIM);
	std::getline(isline, itemname, DELIM);
	std::getline(isline, weight, DELIM);
	std::getline(isline, length, DELIM);
	std::getline(isline, width, DELIM);
	std::getline(isline, height, DELIM);
	std::getline(isline, day, DELIM);
	std::getline(isline, month, DELIM);
	std::getline(isline, year, DELIM);
	std::getline(isline, isAssigned);
	date d(std::stoi(day), std::stoi(month), std::stoi(year));
	Package p(std::stoi(id), stadd, city, prov, itemname, std::stod(weight), std::stod(length), std::stod(width), std::stod(height), d);
	if (isAssigned == "true")
		p.setAssigned();
	return p;
}
std::string Package::toString(void) {
	std::string isA;
	if (isAssigned == true)
		isA = "Yes";
	else
		isA = "No";
	return ID + "" + ItemName + "" +
}