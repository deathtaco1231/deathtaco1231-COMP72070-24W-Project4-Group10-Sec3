#pragma once
#define MGRFNAME "Managers.txt"
#include "AllHeaders.h"
#include "Person.h"

class Manager : public Person {
protected:
	std::string Authkey;
public:
	Manager();
	Manager(std::string);
	Manager(std::string, int, int, std::string, std::string, std::string);
	std::string getAuthkey();
};
Manager readManager(std::ifstream&);
bool authMgr(std::string, std::string, std::string);
Manager currManager;