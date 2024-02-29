#include "AllHeaders.h"
class Person {
protected:
	int ID, Age;
	std::string Name;
	std::string Username;
	std::string Password;
public:
	Person();
	Person(int, int, std::string, std::string, std::string);
	std::string getName();
	void setName(std::string);
	int getAge();
	void setAge(int);
	int getID();
	std::string getUsername();
	std::string getPassword();
	char* getNameCStr();
};