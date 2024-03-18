#include "Address.h"
Address::Address() {
	this->City = "Empty";
	this->stAddr = "Empty";
	this->Province = "Empty";
	this->unitno = 0;
}
Address::Address(std::string staddr, std::string city, std::string prov) {
	this->unitno = 0;
	this->stAddr = staddr;
	this->City = city;
	this->Province = prov;
}
Address::Address(std::string streetad, std::string city, std::string prov, int unitno) {
	this->unitno = unitno;
	this->stAddr = streetad;
	this->City = city;
	this->Province = prov;
}
std::string Address::getCity() {
	return this->City;
}
std::string Address::getProvince() {
	return this->Province;
}
std::string Address::getstAddr() {
	if (this->unitno != 0)
		return this->stAddr + " Unit #" + std::to_string(this->unitno) + ", " + this->City + ", " + this->Province;
	return this->stAddr + ", " + this->City + ", " + this->Province;
}
int Address::getUnitNo() {
	return this->unitno;
}
std::string Address::getOnlySt() {
	return this->stAddr;
}
	
void setProvVector(std::vector<std::string>& a) {
	std::ifstream lolz;
	lolz.open(PROVFPATH);
	if (!lolz.is_open()) 
		exit(-1);
	
	while (!lolz.eof()) {
		std::string tmp;
		std::getline(lolz, tmp);
		a.push_back(tmp);
	}
	lolz.close();
}