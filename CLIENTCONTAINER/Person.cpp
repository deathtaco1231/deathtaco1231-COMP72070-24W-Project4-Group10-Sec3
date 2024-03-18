#include "Person.h"
Person2::Person2() {
	this->Age = 0;
	this->Name = "UNNAMED";
	this->ID = NULL;
}
Person2::Person2(int a, int id, std::string name) {
	this->Age = a;
	this->ID = id;
	this->Name = name;
}
std::string Person2::getName() {
	return this->Name;
}
void Person2::setName(std::string a) {
	this->Name = a;
}
int Person2::getAge() {
	return this->Age;
}
void Person2::setAge(int a) {
	this->Age = a;
}
int Person2::getID() {
	return this->ID;
}
char* Person2::getNameCStr() {
	return (char*)this->Name.c_str();
}