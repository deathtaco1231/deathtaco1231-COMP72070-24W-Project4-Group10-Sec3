#include "Networking.h"

void initPkgVect(void) {
	bool morePkg = true;
	while (morePkg) {
		DataPkt p = recvPacket();
		if (p.getFlags() == PKGENDFLAG)
			morePkg = false;
		else {
			std::istringstream isline(p.getTBuf());
			std::string id, itemname, labelpath, weight, length, width, height, year, month, day, st, unit, city, prov;
			std::getline(isline, id, DELIM);
			std::getline(isline, itemname, DELIM);
			std::getline(isline, labelpath, DELIM);
			std::getline(isline, weight, DELIM);
			std::getline(isline, length, DELIM);
			std::getline(isline, width, DELIM);
			std::getline(isline, height, DELIM);
			std::getline(isline, year, DELIM);
			std::getline(isline, month, DELIM);
			std::getline(isline, day, DELIM);
			std::getline(isline, st, DELIM);
			std::getline(isline, unit, DELIM);
			std::getline(isline, city, DELIM);
			std::getline(isline, prov, BODYEND);
			date d(std::stoi(day), std::stoi(month), std::stoi(year));
			Package p(labelpath, std::stoi(id), st, city, prov, std::stoi(unit), itemname, std::stod(weight), std::stod(length), std::stod(width), std::stod(height), d);
			allPkgs.push_back(p);
			DataPkt img = recvPacket();
			std::istringstream imgline(img.getTBuf());
			std::string imgdata;
			std::getline(imgline, imgdata, BODYEND);
			int size = img.getDSize();
			FILE* fp = fopen(labelpath.c_str(), "wb");
			fwrite(imgdata.c_str(), size, 1, fp);
			fclose(fp);
		}
	}
}
bool authCourier(void) {
	DataPkt p = recvPacket();
	if (p.getFlags() == FAILEDAUTHFLAG)
		return false;
	std::istringstream isline(p.getTBuf());
	std::string gooddeliv, latedeliv, age, id, name;
	std::getline(isline, gooddeliv, DELIM);
	std::getline(isline, latedeliv, DELIM);
	std::getline(isline, age, DELIM);
	std::getline(isline, id, DELIM);
	std::getline(isline, name, BODYEND);
	currCourier = Courier(stoi(gooddeliv), stoi(latedeliv), stoi(age), stoi(id), name);
	return true;
}
void sendToSrv(char* Tx, int size) {
	send(ClientSocket, Tx, size, 0);
}
void sendData(std::string uname, std::string pword) {
	DataPkt p;
	p.setHead(LOGINDT, 0, uname.size() + pword.size() + sizeof(DELIM) + sizeof(BODYEND));
	char dbuf[200];
	strcpy_s(dbuf, uname.c_str());
	strcat(dbuf, ",");
	strcat(dbuf, pword.c_str());
	strcat(dbuf, ";");
	int size;
	p.setTBuf(dbuf, size);
	char* Tx = p.getTBuf();
	sendToSrv(Tx, size);
}
long int GetFileSize(const char* filename)
{
	long int size;
	FILE* f;

	f = fopen(filename, "rb");
	if (f == NULL) return -1;
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fclose(f);

	return size;
}
void logRecv(DataPkt& p) {
	time_t now = time(0);
	char* dt = ctime(&now);
	std::ofstream out("DataLog.txt", std::ios::app);
	out << "Date & Time: " << dt << std::endl;
	out << "Type: " << std::to_string(p.getDType()) << std::endl;
	out << "Flag: " << std::to_string(p.getFlags()) << std::endl;
	out << "Size: " << std::to_string(p.getDSize()) << std::endl;
	out << "Sequence: " << std::to_string(p.getSeqNum()) << std::endl;
	out.close();
}
DataPkt recvPacket(void) {
	char Rx[100000];
	recv(ClientSocket, Rx, sizeof(Rx), 0);
	DataPkt p(Rx);
	logRecv(p);
	return p;
}