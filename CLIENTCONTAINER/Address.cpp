#include "Address.h"
Address2::Address2() {
	this->City = "Empty";
	this->stAddr = "Empty";
	this->Province = "Empty";
	this->unitno = 0;
}
Address2::Address2(std::string staddr, std::string city, std::string prov) {
	this->unitno = 0;
	this->stAddr = staddr;
	this->City = city;
	this->Province = prov;
}
Address2::Address2(std::string streetad, std::string city, std::string prov, int unitno) {
	this->unitno = unitno;
	this->stAddr = streetad;
	this->City = city;
	this->Province = prov;
}
std::string Address2::getCity() {
	return this->City;
}
std::string Address2::getProvince() {
	return this->Province;
}
std::string Address2::getstAddr() {
	if (this->unitno != 0)
		return this->stAddr + " Unit #" + std::to_string(this->unitno) + ", " + this->City + ", " + this->Province;
	return this->stAddr + ", " + this->City + ", " + this->Province;
}
int Address2::getUnitNo() {
	return this->unitno;
}
std::string Address2::getOnlySt() {
	return this->stAddr;
}