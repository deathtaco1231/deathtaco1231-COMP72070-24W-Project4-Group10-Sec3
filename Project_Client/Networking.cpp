#include "Networking.h"
#include "Package.h"

void sendFlag(int VAL) {
	switch (VAL)
	{
	case 1:
	{
		DataPkt s;
		s.setHead(0, FAILEDAUTHFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToClt(s.getTBuf(), size);
		break;
	}
	case 2:
	{
		DataPkt s;
		s.setHead(0, PKGENDFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToClt(s.getTBuf(), size);
		break;
	}
	case 3:
	{
		DataPkt s;
		s.setHead(0, ACKFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToClt(s.getTBuf(), size);
		break;
	}
	case 4:
	{
		DataPkt s;
		s.setHead(0, DELIVFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToClt(s.getTBuf(), size);
		break;
	} 
	case 5:
	{
		DataPkt s;
		s.setHead(0, REJECTFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToClt(s.getTBuf(), size);
		break;
	}
	default:
	{
		DataPkt s;
		s.setHead(0, ERRFLAG, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToClt(s.getTBuf(), size);
		break;
	}
	}
}
void sendCltPackages(void) {
	DataPkt p;
	std::string tmp;
	for (int i = 0; i < allPkgs.size(); i++) {
		if (allPkgs[i].checkifassigned() == true) {
			Sleep(50);
			char cbuf[5000] = { 0 };
			strcpy_s(cbuf, std::to_string(allPkgs[i].getID()).c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, allPkgs[i].getItem().c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, allPkgs[i].getImgPath().c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, std::to_string(allPkgs[i].getWeight()).c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, std::to_string(allPkgs[i].getLength()).c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, std::to_string(allPkgs[i].getWidth()).c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, std::to_string(allPkgs[i].getHeight()).c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, std::to_string(allPkgs[i].getDeliverBy().getyear()).c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, std::to_string(allPkgs[i].getDeliverBy().getmonth()).c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, std::to_string(allPkgs[i].getDeliverBy().getday()).c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, allPkgs[i].getOnlySt().c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, std::to_string(allPkgs[i].getUnitNo()).c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, allPkgs[i].getCity().c_str());
			strcat_s(cbuf, ",");
			strcat_s(cbuf, allPkgs[i].getProvince().c_str());
			strcat_s(cbuf, ";\n");
			p.setHead(PKGDT, 0, strlen(cbuf));
			int size = 0;
			p.setTBuf(cbuf, size);
			Sleep(50);
			sendToClt(p.getTBuf(), size);
			long int len = GetFileSize(allPkgs[i].getImgPath().c_str());
			FILE* in;
			fopen_s(&in, allPkgs[i].getImgPath().c_str(), "rb");
			char buf[100000] = { 0 };
			fread(buf, 1, len, in);
			fclose(in);
			char strlen[8] = { 0 };
			_itoa_s(len, strlen, 10);
			Sleep(50);
			sendToClt(strlen, sizeof(strlen));
			Sleep(50);
			sendToClt(buf, len);
		}
	}
	sendFlag(PKGENDFLAG);
}
long int GetFileSize(const char* filename)
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
void sendToClt(char* Tx, int size) {
	send(ConnectionSocket, Tx, size, 0);
}
void logRecv(DataPkt& p) {
	time_t now = time(0);
	char dt[100] = { 0 };
	ctime_s(dt, sizeof(dt), &now);
	std::ofstream out("DataLog.txt", std::ios::app);
	out << "RECV Date & Time: " << dt;
	out << "Type: " << std::to_string(p.getDType()) << std::endl;
	out << "Flag: " << std::to_string(p.getFlags()) << std::endl;
	out << "Size: " << std::to_string(p.getDSize()) << std::endl;
	out << "Sequence: " << std::to_string(p.getSeqNum()) << std::endl;
	out.close();
}
DataPkt recvPacket(void) {
	char Rx[500000];
	recv(ConnectionSocket, Rx, sizeof(Rx), 0);
	DataPkt p(Rx);
	logRecv(p);
	return p;
}
