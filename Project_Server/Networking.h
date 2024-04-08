#pragma once
#define FAILEDAUTHFLAG 1
#define PKGENDFLAG 2
#define ACKFLAG 3
#define DELIVFLAG 4
#define REQPACKAGEFLAG 6
#define ERRFLAG 10
#define EXITFLAG 12
#include "AllHeaders.h"
#include "DataPacket.h"
#include "Courier.h"
#include "Package.h"

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
	bool connecting = true;
	while (connecting) {
		if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) != SOCKET_ERROR)
			connecting = false;
	}
	/*if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return false;
	}*/
	return true;
}
void recvBuf(char* buf, int len) {
	recv(ClientSocket, buf, len, 0);
}
bool sendDelivered(std::string label, Package& p);
void sendFlag(int);
void sendToSrv(char* Tx, int size);
void sendData(std::string uname, std::string pword);
long int GetFileSize(const char* filename);
void logRecv(DataPkt& p);
DataPkt recvPacket(void);
bool authCourier(void);
void initPkgVect(void);
Package recvPackage(DataPkt&);