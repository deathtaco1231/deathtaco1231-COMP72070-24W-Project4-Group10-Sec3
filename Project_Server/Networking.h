#include "AllHeaders.h"
#include "DataPacket.h"

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
	p.setHead(LOGINDT, 0, uname.size() + pword.size());
	char dbuf[200];
	strcpy_s(dbuf, uname.c_str());
	strcat(dbuf, ",");
	strcat()
	p.setTBuf
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