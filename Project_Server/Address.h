#pragma once
#include "AllHeaders.h"
class Address {
protected:
	std::string stAddr;
	int unitno;
	std::string City;
	std::string Province;
public:
	Address();
	Address(std::string, std::string, std::string);
	Address(std::string, std::string, std::string, int);
	void setProvince(std::string);
	void setstAddr(std::string);
	void setCity(std::string);
	void setUnitNo(int);
	int getUnitNo();
	std::string getCity();
	std::string getstAddr();
	std::string getProvince();
};