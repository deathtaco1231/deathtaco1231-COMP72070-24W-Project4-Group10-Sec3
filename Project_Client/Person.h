#include "AllHeaders.h"
class Person {
protected:
	std::string Name;
	int Age;
public:
	Person();
	Person(int, std::string);
	std::string getName();
	void setName(std::string);
	int getAge();
	void setAge(int);
	char* getNameCStr();
};