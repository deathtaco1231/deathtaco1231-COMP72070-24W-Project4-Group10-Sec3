#include "Networking.h"

void initPkgVect2(void) {
	bool morePkg = true;
	while (morePkg) {

		DataPkt2 p = recvPacket2();
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
			date2 d(std::stoi(day), std::stoi(month), std::stoi(year));
			Package2 p(labelpath, std::stoi(id), st, city, prov, std::stoi(unit), itemname, std::stod(weight), std::stod(length), std::stod(width), std::stod(height), d);
			allPkgs2.push_back(p);

			char len[8] = { 0 };
			recvBuf2(len, sizeof(len));
			long int reallen = atoi(len);
			char buf[100000] = { 0 };
			recvBuf2(buf, reallen);
			FILE* fp;
			fopen_s(&fp, labelpath.c_str(), "wb");
			fwrite(buf, reallen, 1, fp);
			fclose(fp);
		}
	}
}
void sendFlag2(int VAL) {
	switch (VAL)
	{
	case 1:
	{
		DataPkt2 s;
		s.setHead(0, FAILEDAUTHFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
	}
	case 2:
	{
		DataPkt2 s;
		s.setHead(0, PKGENDFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
	}
	case 3:
	{
		DataPkt2 s;
		s.setHead(0, ACKFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
	}
	case 4:
	{
		DataPkt2 s;
		s.setHead(0, DELIVFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
	}
	default:
	{
		DataPkt2 s;
		s.setHead(0, ERRFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToSrv(s.getTBuf(), size);
		break;
	}
	}
}
bool authCourier2(void) {
	DataPkt2 p = recvPacket2();
	if (p.getFlags() == FAILEDAUTHFLAG)
		return false;
	std::istringstream isline(p.getTBuf());
	std::string gooddeliv, latedeliv, age, id, name;
	std::getline(isline, gooddeliv, DELIM);
	std::getline(isline, latedeliv, DELIM);
	std::getline(isline, age, DELIM);
	std::getline(isline, id, DELIM);
	std::getline(isline, name, BODYEND);
	currCourier2 = Courier2(stoi(gooddeliv), stoi(latedeliv), stoi(age), stoi(id), name);
	return true;
}
void sendToSrv(char* Tx, int size) {
	send(ClientSocket, Tx, size, 0);
}
void sendData2(std::string uname, std::string pword) {
	DataPkt2 p;
	p.setHead(LOGINDT, 0, uname.size() + pword.size() + sizeof(DELIM) + sizeof(BODYEND));
	char dbuf[200];
	strcpy_s(dbuf, uname.c_str());
	strcat_s(dbuf, ",");
	strcat_s(dbuf, pword.c_str());
	strcat_s(dbuf, ";");
	int size;
	p.setTBuf(dbuf, size);
	char* Tx = p.getTBuf();
	sendToSrv(Tx, size);
}
long int GetFileSize2(const char* filename)
{
	long int size;
	FILE* f;

	fopen_s(&f, filename, "rb");
	if (f == NULL) return -1;
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fclose(f);

	return size;
}
void logRecv2(DataPkt2& p) {
	time_t now = time(0);
	char dt[100];
	ctime_s(dt, sizeof(now), &now);
	std::ofstream out("DataLog.txt", std::ios::app);
	out << "Date & Time: " << dt << std::endl;
	out << "Type: " << std::to_string(p.getDType()) << std::endl;
	out << "Flag: " << std::to_string(p.getFlags()) << std::endl;
	out << "Size: " << std::to_string(p.getDSize()) << std::endl;
	out << "Sequence: " << std::to_string(p.getSeqNum()) << std::endl;
	out.close();
}
DataPkt2 recvPacket2(void) {
	char Rx[100000];
	recv(ClientSocket, Rx, sizeof(Rx), 0);
	DataPkt2 p(Rx);
	logRecv2(p);
	return p;
}
bool sendDelivered2(std::string label, Package2& p) {
	sendFlag2(DELIVFLAG);
	char cbuf[5000] = { 0 };
	strcpy_s(cbuf, std::to_string(p.getID()).c_str());
	strcat_s(cbuf, ";\n");
	DataPkt2 d;
	d.setHead(PKGDT, DELIVFLAG, strlen(cbuf));
	int size = 0;
	d.setTBuf(cbuf, size);
	Sleep(50);
	sendToSrv(d.getTBuf(), size);
	long int len = GetFileSize2(label.c_str());
	FILE* in;
	fopen_s(&in, label.c_str(), "rb");
	char buf[100000] = { 0 };
	fread(buf, 1, len, in);
	fclose(in);
	char strlen[8] = { 0 };
	_itoa_s(len, strlen, 10);
	Sleep(50);
	sendToSrv(strlen, sizeof(strlen));
	Sleep(50);
	sendToSrv(buf, len);
	DataPkt2 n = recvPacket2();
	if (n.getFlags() == ACKFLAG)
		return true;
	else
		return false;
}