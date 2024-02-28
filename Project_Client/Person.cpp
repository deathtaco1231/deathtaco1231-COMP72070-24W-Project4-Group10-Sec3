#include "Person.h"
Person::Person() {
	this->Age = 0;
	this->Name = "UNNAMED";
}
Person::Person(int a, std::string b) {
	this->Age = a;
	this->Name = b;
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
char* Person::getNameCStr() {
	return (char*)this->Name.c_str();
}