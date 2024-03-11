#include "Manager.h"
Manager::Manager() : Person() {
	this->Authkey = "";
}
Manager::Manager(std::string auth) : Person() {
	this->Authkey = auth;
}
Manager::Manager(std::string auth, int a, int id, std::string name, std::string username, std::string password) : Person(a, id, name, username, password) {
	this->Authkey = auth;
}
Manager readManager(QFile& in) {
	QString line = in.readLine();
	std::string authkey, age, id, name, uname, pword;
	std::istringstream isline(line.toStdString());
	std::getline(isline, authkey, DELIM);
	std::getline(isline, age, DELIM);
	std::getline(isline, id, DELIM);
	std::getline(isline, name, DELIM);
	std::getline(isline, uname, DELIM);
	std::getline(isline, pword);
	Manager m(authkey, stoi(age), stoi(id), name, uname, pword);
	return m;
}
std::string Manager::getAuthkey(void) {
	return this->Authkey;
}
bool authMgr(std::string uname, std::string pword, std::string authkey) {
	QFile mgrdata(MGRFNAME);
	if (!mgrdata.open(QIODevice::ReadOnly)) {
		qDebug("Failed to open manager data file.");
		return false;
	}
	while (!mgrdata.atEnd()) {
		Manager tmp = readManager(mgrdata);
		if (tmp.getUsername() == uname) {
			if (tmp.getPassword() == pword && tmp.getAuthkey() == authkey) {
				currManager = tmp;
				mgrdata.close();
				return true;
			}
		}
	}
	mgrdata.close();
	return false;
}