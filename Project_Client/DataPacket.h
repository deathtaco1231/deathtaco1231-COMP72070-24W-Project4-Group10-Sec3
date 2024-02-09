#pragma once
#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
class Address {
protected:
	std::string stAddr;
	int unitno;
	std::string City;
	std::string Province;
public:
	Address();
	Address(std::string, std::string, std::string, int);
	~Address();
	void setProvince(std::string);
	void setstAddr(std::string);
	void setCity(std::string);
	void setUnitNo(int);
	int getUnitNo();
	std::string getCity();
	std::string getstAddr();
	std::string getProvince();

};
void setProvVector(std::vector<std::string>*);
class Package : public Address{
protected:
	std::string ItemName;
	std::string deliverBy;
	std::string createdOn;
public:
	Package();
	~Package();
};
class Header {

};
class DataPkt {
public:
	Header head;
};