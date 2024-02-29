#include "Person.h"
Person::Person() {
	this->Age = 0;
	this->Name = "UNNAMED";
	this->ID = NULL;
	this->Username = "";
	this->Password = "";
}
Person::Person(int a, int id, std::string name, std::string username, std::string password) {
	this->Age = a;
	this->ID = id;
	this->Name = name;
	this->Username = username;
	this->Password = password;
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
std::string Person::getUsername() {
	return this->Username;
}
std::string Person::getPassword() {
	return this->Password;
}
char* Person::getNameCStr() {
	return (char*)this->Name.c_str();
}