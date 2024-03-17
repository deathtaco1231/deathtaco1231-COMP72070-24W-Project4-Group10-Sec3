#pragma once
#include "AllHeaders.h"
class Person2 {
protected:
	int ID, Age;
	std::string Name;
public:
	Person2();
	Person2(int, int, std::string);
	std::string getName();
	void setName(std::string);
	int getAge();
	void setAge(int);
	int getID();
	char* getNameCStr();
};