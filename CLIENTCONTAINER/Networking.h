#pragma once
#define FAILEDAUTHFLAG 1
#define PKGENDFLAG 2
#define ACKFLAG 3
#define DELIVFLAG 4
#define ERRFLAG 10
#include "AllHeaders.h"
#include "DataPacket.h"
#include "Courier.h"
#include "Package.h"

SOCKET ClientSocket;
bool initCltSocket() {
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
void recvBuf2(char* buf, int len) {
	recv(ClientSocket, buf, len, 0);
}
bool sendDelivered2(std::string label, Package2& p);
void sendFlag2(int);
void sendToSrv(char* Tx, int size);
void sendData2(std::string uname, std::string pword);
long int GetFileSize2(const char* filename);
void logRecv2(DataPkt2& p);
DataPkt2 recvPacket2(void);
bool authCourier2(void);
void initPkgVect2(void);