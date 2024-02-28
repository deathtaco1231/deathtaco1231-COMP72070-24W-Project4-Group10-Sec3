#include "AllHeaders.h"
#include "Address.h"
#include "Date.h"
class Package : public Address {
protected:
	std::string ItemName;
	double weight, length, width, height;
	date deliverBy;
	date createdOn;
	
public:
	Package();
	Package(std::string, double, double, double, double, date);
	Package(std::string, std::string, std::string, std::string, double, double, double, double, date);
	Package(std::string, std::string, std::string, int, std::string, double, double, double, double, date);
	void setItem(std::string);
	void setWeight(double);
	void setLength(double);
	void setWidth(double);
	void setHeight(double);
	void setDeliverBy(date);
	std::string getItem();
	double getWeight();
	double getLength();
	double getWidth();
	double getHeight();
	date getDeliverBy();
	date getCreationDate();
};

