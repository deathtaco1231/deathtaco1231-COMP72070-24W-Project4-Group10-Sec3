#include "Person.h"
Person::Person() {
	this->Age = 0;
	this->Name = "UNNAMED";
	this->ID = NULL;
}
Person::Person(int a, int id, std::string name) {
	this->Age = a;
	this->ID = id;
	this->Name = name;
}
std::string Person::getName() {
	return this->Name;
}
void Person::setName(std::string a) {
	this->Name = a;
}
int Person::getAge() {
	return this->Age;
}
void Person::setAge(int a) {
	this->Age = a;
}
int Person::getID() {
	return this->ID;
}
char* Person::getNameCStr() {
	return (char*)this->Name.c_str();
}