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
			
			char len[8] = { 0 };
			recvBuf(len, sizeof(len));
			long int reallen = atoi(len);
			char buf[100000] = { 0 };
			recvBuf(buf, reallen);
			FILE* fp = fopen(labelpath.c_str(), "wb");
			fwrite(buf, reallen, 1, fp);
			fclose(fp);
		}
	}
}
void sendFlag(int VAL) {
	switch (VAL)
	{
	case 1:
	{
		DataPkt s;
		s.setHead(0, FAILEDAUTHFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
	}
	case 2:
	{
		DataPkt s;
		s.setHead(0, PKGENDFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
	}
	case 3:
	{
		DataPkt s;
		s.setHead(0, ACKFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
	}
	case 4:
	{
		DataPkt s;
		s.setHead(0, DELIVFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
	}
	case EXITFLAG:
	{
		DataPkt s;
		s.setHead(0, EXITFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
	}
	case REQPACKAGEFLAG: 
	{
		DataPkt s;
		s.setHead(0, REQPACKAGEFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
	}
	default:
	{
		DataPkt s;
		s.setHead(0, ERRFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
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
	//char Rx[200000];
	char* Rx = new char[200000] {0};
	recv(ClientSocket, Rx, 200000, 0);
	DataPkt p(Rx);
	delete[] Rx;
	logRecv(p);
	return p;
}
bool sendDelivered(std::string label, Package& p) {
	sendFlag(DELIVFLAG);
	char cbuf[5000] = { 0 };
	strcpy_s(cbuf, std::to_string(p.getID()).c_str());
	strcat_s(cbuf, ";\n");
	DataPkt d;
	d.setHead(PKGDT, DELIVFLAG, strlen(cbuf));
	int size = 0;
	d.setTBuf(cbuf, size);
	Sleep(50);
	sendToSrv(d.getTBuf(), size);
	long int len = GetFileSize(label.c_str());
	FILE* in = fopen(label.c_str(), "rb");
	char* buf = new char[200000]{ 0 };
	fread(buf, 1, len, in);
	fclose(in);
	char strlen[8] = { 0 };
	_itoa(len, strlen, 10);
	Sleep(50);
	sendToSrv(strlen, sizeof(strlen));
	Sleep(50);
	sendToSrv(buf, len);
	delete[] buf;
	DataPkt n = recvPacket();
	if (n.getFlags() == ACKFLAG)
		return true;
	else
		return false;
}