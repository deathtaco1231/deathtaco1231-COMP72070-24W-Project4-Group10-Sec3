#pragma once
#include "AllHeaders.h"
class Person {
protected:
	int ID, Age;
	std::string Name;
public:
	Person();
	Person(int, int, std::string);
	std::string getName();
	void setName(std::string);
	int getAge();
	void setAge(int);
	int getID();
	char* getNameCStr();
};