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
	this->createdOn = currdate;
	this->isAssigned = false;
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
	this->createdOn = currdate;
	this->isAssigned = false;
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
	this->createdOn = currdate;
	this->isAssigned = false;
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
	this->isAssigned = true;
}
bool Package::checkifassigned(void) {
	return isAssigned;
}
std::string Package::getImgPath(void) {
	return this->LabelImgPath;
}

bool initPkgVect(std::string fname) {
	std::ifstream pkgdata;
	pkgdata.open(fname);
	if (!pkgdata.is_open())
		return false;
	while (!pkgdata.eof()) {
		Package tmp = readPkg(pkgdata);
		allPkgs.push_back(tmp);
	}
	pkgdata.close();
	return true;
}
Package readPkg(std::ifstream& in) {
	std::string tmpline, labelpath, id, stadd, city, prov, itemname, weight, length, width, height, day, month, year, isAssigned;
	std::getline(in, tmpline);
	std::istringstream isline(tmpline);
	std::getline(isline, labelpath, DELIM);
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
	Package p(labelpath, std::stoi(id), stadd, city, prov, itemname, std::stod(weight), std::stod(length), std::stod(width), std::stod(height), d);
	if (strncmp(isAssigned.c_str(), "true", 4) == 0)
		p.setAssigned();
	return p;
}
std::string Package::toString(void) {
	std::string isA;
	if (isAssigned == true)
		isA = "Yes";
	else
		isA = "No";
	std::stringstream s;
	s << ID << "	" << ItemName << "	" << isA << "	" << createdOn.datetos() << "	" << deliverBy.datetos();
	return s.str();
}
Package matchbyID(int i) {
	for (int a = 0; a < allPkgs.size(); a++) {
		if (allPkgs[a].getID() == i)
			return allPkgs[a];
	}
}
//std::string Package::toStringConst(void)const {
//	std::string isA;
//	if (isAssigned == true)
//		isA = "Yes";
//	else
//		isA = "No";
//	std::stringstream s;
//	s << ID << "	" << ItemName << "	" << isA;
//	return s.str();
//}
//inline bool operator == (const Package& a, const Package& b) {
//	if (a.toStringConst() == b.toStringConst())
//		return true;
//	else
//		return false;
//}