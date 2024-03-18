#pragma once
#include "AllHeaders.h"
#include "Address.h"
#include "Date.h"
class Package2 : public Address2 {
protected:
	int ID;
	std::string ItemName;
	std::string LabelImgPath;
	double weight, length, width, height;
	date2 deliverBy;

public:
	Package2();
	Package2(std::string, int, std::string, double, double, double, double, date2);
	Package2(std::string, int, std::string, std::string, std::string, std::string, double, double, double, double, date2);
	Package2(std::string, int, std::string, std::string, std::string, int, std::string, double, double, double, double, date2);
	void setID(int);
	void setItem(std::string);
	void setWeight(double);
	void setLength(double);
	void setWidth(double);
	void setHeight(double);
	void setDeliverBy(date2);
	int getID();
	std::string getItem();
	double getWeight();
	double getLength();
	double getWidth();
	double getHeight();
	date2 getDeliverBy();
	std::string getImgPath();
	std::string toString();
};
std::vector<Package2> allPkgs2;
