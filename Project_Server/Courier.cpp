#include "Courier.h"
Courier::Courier() : Person(){
	this->GoodDeliveries = 0;
	this->LateDeliveries = 0;
}
Courier::Courier(int gooddeliv, int latedeliv) : Person(){
	this->GoodDeliveries = gooddeliv;
	this->LateDeliveries = latedeliv;
}
Courier::Courier(int gooddeliv, int latedeliv, int ID, int Age, std::string Name) : Person(Age, ID, Name){
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