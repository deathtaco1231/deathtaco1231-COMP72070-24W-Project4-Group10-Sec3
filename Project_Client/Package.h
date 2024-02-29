#include "AllHeaders.h"
#include "Address.h"
#include "Date.h"
class Package : public Address {
protected:
	int ID;
	std::string ItemName;
	double weight, length, width, height;
	date deliverBy;
	date createdOn;
	
public:
	Package();
	Package(int, std::string, double, double, double, double, date);
	Package(int, std::string, std::string, std::string, std::string, double, double, double, double, date);
	Package(int, std::string, std::string, std::string, int, std::string, double, double, double, double, date);
	void setID(int);
	void setItem(std::string);
	void setWeight(double);
	void setLength(double);
	void setWidth(double);
	void setHeight(double);
	void setDeliverBy(date);
	int getID();
	std::string getItem();
	double getWeight();
	double getLength();
	double getWidth();
	double getHeight();
	date getDeliverBy();
	date getCreationDate();
};

