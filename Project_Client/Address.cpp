#include "Address.h"
Address::Address() {
	this->City = "Empty";
	this->stAddr = "Empty";
	this->Province = "Empty";
	this->unitno = NULL;
}
Address::Address(std::string staddr, std::string city, std::string prov) {
	this->unitno = 0;
	this->stAddr = staddr;
	this->City = city;
	this->Province = prov;
}
Address::Address(std::string streetad, std::string city, std::string prov, int unitno) {
	this->unitno = unitno;
	this->stAddr = streetad;
	this->City = city;
	this->Province = prov;
}
std::string Address::getCity() {
	return this->City;
}
std::string Address::getProvince() {
	return this->Province;
}


void setProvVector(std::vector<std::string>& a) {
	QFile lolz(PROVFPATH);
	if (!lolz.open(QIODevice::ReadOnly)) {
		qDebug("\nPROVINCE LIST FILE NOT FOUND. ABORTING...");
		exit(-1);
	}
	while (!lolz.atEnd()) {
		QString tmp = lolz.readLine();
		a.push_back(tmp.toStdString());
	}
	lolz.close();
}