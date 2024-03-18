#pragma once
#define FAILEDAUTHFLAG 1
#define PKGENDFLAG 2
#define ACKFLAG 3
#define DELIVFLAG 4
#define REJECTFLAG 5
#define ERRFLAG 10
#define TMPIMG "TEMP.jpg"
#include "AllHeaders.h"
#include "DataPacket.h"

SOCKET ServerSocket, ConnectionSocket;
bool initSocket(void) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return false;

	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}
	
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_addr.s_addr = INADDR_ANY;
	SvrAddr.sin_port = htons(27000);
	if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR)
	{
		closesocket(ServerSocket);
		WSACleanup();
		return false;
	}

	if (listen(ServerSocket, 1) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return false;
	}
	return true;
}
bool connectSocket(void) {
	ConnectionSocket = SOCKET_ERROR;
	if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return false;;
	}
	return true;
}
void recvBuf(char* buf, int len) {
	recv(ConnectionSocket, buf, len, 0);
}
void sendFlag(int);	
long int GetFileSize(const char* filename); 
void sendToClt(char* Tx, int size);
void logRecv(DataPkt& p);
DataPkt recvPacket(void);
void sendCltPackages(void);

