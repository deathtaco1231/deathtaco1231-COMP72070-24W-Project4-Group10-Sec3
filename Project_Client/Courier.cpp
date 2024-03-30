#include "Courier.h"
Courier::Courier() : Person(){
	this->GoodDeliveries = 0;
	this->LateDeliveries = 0;
}
Courier::Courier(int gooddeliv, int latedeliv) : Person(){
	this->GoodDeliveries = gooddeliv;
	this->LateDeliveries = latedeliv;
}
Courier::Courier(int gooddeliv, int latedeliv, int Age, int ID, std::string Name, std::string Username, std::string Password) : Person(Age, ID, Name, Username, Password){
	this->GoodDeliveries = gooddeliv;
	this->LateDeliveries = latedeliv;
}  
void Courier::incGoodDeliv() {
	this->GoodDeliveries++;
}
void Courier::incLateDeliv() {
	this->LateDeliveries++;
}
int Courier::getGoodDeliv() {
	return this->GoodDeliveries;
}
int Courier::getLateDeliv() {
	return this->LateDeliveries;
}
Courier readCourier(std::ifstream& in) {
	std::string tmpline, gooddeliv, latedeliv, age, id, name, uname, pword;
	std::getline(in, tmpline);
	std::istringstream isline(tmpline);
	std::getline(isline, gooddeliv, DELIM);
	std::getline(isline, latedeliv, DELIM);
	std::getline(isline, age, DELIM);
	std::getline(isline, id, DELIM);
	std::getline(isline, name, DELIM);
	std::getline(isline, uname, DELIM);
	std::getline(isline, pword, BODYEND);
	Courier c(stoi(gooddeliv), stoi(latedeliv), stoi(age), stoi(id), name, uname, pword);
	return c;
}
bool authCourier(std::string uname, std::string pword) {
	std::ifstream courierdata;
	courierdata.open(COURIERFNAME);
	if (!courierdata.is_open()) {
		return false;
	}
	while (!courierdata.eof()) {
		Courier tmp = readCourier(courierdata);
		if (tmp.getUsername() == uname) {
			if (tmp.getPassword() == pword) {
				currCourier = tmp;
				courierdata.close();
				return true;
			}
		}
	}
	courierdata.close();
	return false;
}
void sendCourier(Courier c) {
	DataPkt p;
	std::string tmp;
	char cbuf[1000] = { 0 };
	strcpy_s(cbuf, std::to_string(c.getGoodDeliv()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, std::to_string(c.getLateDeliv()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, std::to_string(c.getAge()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, std::to_string(c.getID()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, c.getName().c_str());
	strcat_s(cbuf, ";\n");
	p.setHead(COURIERDT, 0, strlen(cbuf));
	int size;
	p.setTBuf(cbuf, size);
	sendToClt(p.getTBuf(), size);
}
void setCurrentCourier(void) {
	bool isValid = false;
	while (!isValid) {
		DataPkt p = recvPacket();
		std::istringstream isline(p.getTBuf());
		std::string uname, pword;
		std::getline(isline, uname, DELIM);
		std::getline(isline, pword, BODYEND);
		if (!authCourier(uname, pword)) 
			sendFlag(FAILEDAUTHFLAG);
		else {
			isValid = true;
			sendCourier(currCourier);
		}
	}
}
void writeAllCouriers(void) {
	std::ofstream out(COURIERFNAME);
	for (int i = 0; i < allCouriers.size(); i++) {
		Courier c = allCouriers[i];
		out << c.getGoodDeliv() << DELIM << c.getLateDeliv() << DELIM << c.getAge() << DELIM << c.getID() << DELIM << c.getName() << DELIM << c.getUsername() << DELIM << c.getPassword() << std::endl;
	}
	out.close();
}
void setCourierVect(void) {
	std::ifstream courierdata;
	courierdata.open(COURIERFNAME);
	if (!courierdata.is_open())
		exit(1);
	while (!courierdata.eof()) {
		Courier tmp = readCourier(courierdata);
		allCouriers.push_back(tmp);
	}
	courierdata.close();
}
