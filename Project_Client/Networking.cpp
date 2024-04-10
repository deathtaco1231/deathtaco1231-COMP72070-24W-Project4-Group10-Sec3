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
DataPkt fmtPkg(Package& pkg, int& size) {
	DataPkt p;
	char cbuf[5000] = { 0 };
	strcpy_s(cbuf, std::to_string(pkg.getID()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, pkg.getItem().c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, pkg.getImgPath().c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, std::to_string(pkg.getWeight()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, std::to_string(pkg.getLength()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, std::to_string(pkg.getWidth()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, std::to_string(pkg.getHeight()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, std::to_string(pkg.getDeliverBy().getyear()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, std::to_string(pkg.getDeliverBy().getmonth()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, std::to_string(pkg.getDeliverBy().getday()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, pkg.getOnlySt().c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, std::to_string(pkg.getUnitNo()).c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, pkg.getCity().c_str());
	strcat_s(cbuf, ",");
	strcat_s(cbuf, pkg.getProvince().c_str());
	strcat_s(cbuf, ";\n");
	p.setHead(PKGDT, 0, strlen(cbuf));
	size = 0;
	p.setTBuf(cbuf, size);
	return p;
}
void sendCltPackages(void) {
	std::string tmp;
	for (int i = 0; i < allPkgs.size(); i++) {
		if (allPkgs[i].checkifassigned() == true) {
			int size;
			DataPkt p = fmtPkg(allPkgs[i], size);
			Sleep(100);
			sendToClt(p.getTBuf(), size);
			long int len = GetFileSize(allPkgs[i].getImgPath().c_str());
			FILE* in;
			fopen_s(&in, allPkgs[i].getImgPath().c_str(), "rb");
			char* buf = new char[200000]{ 0 };
			fread(buf, 1, len, in);
			fclose(in);
			char strlen[8] = { 0 };
			_itoa_s(len, strlen, 10);
			Sleep(100);
			sendToClt(strlen, sizeof(strlen));
			Sleep(150);
			sendToClt(buf, len);
			delete[] buf;
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
	//char Rx[200000];
	char* Rx = new char[200000] {0};
	recv(ConnectionSocket, Rx, 200000, 0);
	DataPkt p(Rx);
	delete[] Rx;
	logRecv(p);
	return p;
}
