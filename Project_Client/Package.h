#pragma once
#define PKGFNAME "Packages.txt"
#include "AllHeaders.h"
#include "Address.h"
#include "Date.h"
class Package : public Address {
protected:
	int ID;
	bool isAssigned;
	std::string ItemName;
	std::string LabelImgPath;
	double weight, length, width, height;
	date deliverBy;
	date createdOn;
	
public:
	Package();
	Package(std::string, int, std::string, double, double, double, double, date);
	Package(std::string, int, std::string, std::string, std::string, std::string, double, double, double, double, date);
	Package(std::string, int, std::string, std::string, std::string, int, std::string, double, double, double, double, date);
	void setID(int);
	void setItem(std::string);
	void setWeight(double);
	void setLength(double);
	void setWidth(double);
	void setHeight(double);
	void setDeliverBy(date);
	void setAssigned();
	int getID();
	std::string getItem();
	double getWeight();
	double getLength();
	double getWidth();
	double getHeight();
	bool checkifassigned();
	date getDeliverBy();
	date getCreationDate();
	std::string getImgPath();
	std::string toString();
	/*std::string toStringConst()const;*/
};
//inline bool operator == (const Package&, const Package&);
std::vector<Package> allPkgs;
Package tmpPkg;
bool isDel;
bool initPkgVect(void);
Package readPkg(std::ifstream&);
Package matchbyID(int i);
void writeAllPackages(void);
void setVectPkgAssigned(Package&);



