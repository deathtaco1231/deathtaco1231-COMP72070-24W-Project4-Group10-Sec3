#include "DataPacket.h"

void setProvVector(std::vector<std::string>* a) {
	std::ifstream lolz;
	lolz.open("provinces.txt");
	if (!lolz.is_open()) {
		std::cout << "\nPROVINCE LIST FILE NOT FOUND. ABORTING...";
		exit(-1);
	}
	for (int i = 0; i <= 13; i++) {
		std::string tmp;
		lolz >> tmp;               
		a->push_back(tmp);
	}
}

Address::Address() {
	this->City = "Empty";
	this->stAddr = "Empty";
	this->Province = "Empty";
	this->unitno = NULL;
}
Address::Address(std::string streetad, std::string city, std::string prov, int unitno) {
	this->unitno = unitno;
	this->stAddr = streetad;
	this->City = city;
	this->Province = prov;
}
Address::~Address() {

}
void setProvince(std::string);
void setstAddr(std::string);
void setCity(std::string);
void setUnitNo(int);
int getUnitNo();
std::string Address::getCity() {
	return this->City;
}
std::string getstAddr();
std::string Address::getProvince() {
	return this->Province;
}
