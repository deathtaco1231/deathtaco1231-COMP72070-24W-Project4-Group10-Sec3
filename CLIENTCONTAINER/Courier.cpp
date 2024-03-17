#include "Courier.h"
Courier2::Courier2() : Person2() {
	this->GoodDeliveries = 0;
	this->LateDeliveries = 0;
}
Courier2::Courier2(int gooddeliv, int latedeliv) : Person2() {
	this->GoodDeliveries = gooddeliv;
	this->LateDeliveries = latedeliv;
}
Courier2::Courier2(int gooddeliv, int latedeliv, int Age, int ID, std::string Name) : Person2(Age, ID, Name) {
	this->GoodDeliveries = gooddeliv;
	this->LateDeliveries = latedeliv;
}
void Courier2::incGoodDeliv() {
	this->GoodDeliveries++;
}
void Courier2::incLateDeliv() {
	this->LateDeliveries++;
}
int Courier2::getGoodDeliv() {
	return this->GoodDeliveries;
}
int Courier2::getLateDeliv() {
	return this->LateDeliveries;
}