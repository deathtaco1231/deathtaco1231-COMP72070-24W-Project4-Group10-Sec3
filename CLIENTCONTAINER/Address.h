#pragma once
#include "AllHeaders.h"
class Address2 {
protected:
	std::string stAddr;
	int unitno;
	std::string City;
	std::string Province;
public:
	Address2();
	Address2(std::string, std::string, std::string);
	Address2(std::string, std::string, std::string, int);
	void setProvince(std::string);
	void setstAddr(std::string);
	void setCity(std::string);
	void setUnitNo(int);
	int getUnitNo();
	std::string getCity();
	std::string getstAddr();
	std::string getProvince();
	std::string getOnlySt();
};