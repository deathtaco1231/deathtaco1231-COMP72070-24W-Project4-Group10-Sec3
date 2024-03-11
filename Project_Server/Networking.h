#include "AllHeaders.h"
#include "DataPacket.h"
#include "Courier.h"

SOCKET ClientSocket;
bool initSocket() {
	//starts Winsock DLLs
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		return false;
	}

	//initializes socket. SOCK_STREAM: TCP
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}

	//Connect socket to specified server
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;						//Address family type itnernet
	SvrAddr.sin_port = htons(27000);					//port (host to network conversion)
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//IP address
	if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return false;
	}
	return true;
}
void sendData(std::string uname, std::string pword) {
	DataPkt p;
	p.setHead(LOGINDT, 0, uname.size() + pword.size() + sizeof(DELIM));
	char dbuf[200];
	strcpy_s(dbuf, uname.c_str());
	strcat(dbuf, ",");
	strcat(dbuf, pword.c_str());
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
void sendToSrv(char* Tx, int size) {
	send(ClientSocket, Tx, size, 0);
}
DataPkt recvPacket(void) {
	char Rx[100000];
	recv(ClientSocket, Rx, sizeof(Rx), 0);
	DataPkt p(Rx);
	return p;
}
bool authCourier(void) {
	DataPkt p = recvPacket();
	if (p.getFlags() == 1)
		return false;
	std::istringstream isline(p.getTBuf());
	std::string gooddeliv, latedeliv, age, id, name;
	std::getline(isline, gooddeliv, DELIM);
	std::getline(isline, latedeliv, DELIM);
	std::getline(isline, age, DELIM);
	std::getline(isline, id, DELIM);
	std::getline(isline, name);
	currCourier = Courier(stoi(gooddeliv), stoi(latedeliv), stoi(age), stoi(id), name);
	return true;
}