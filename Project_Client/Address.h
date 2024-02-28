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