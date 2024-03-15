#pragma once
#define FAILEDAUTHFLAG 1
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
	SvrAddr.sin_port = htons(27500);
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
void sendToClt(char* Tx, int size) {
	send(ConnectionSocket, Tx, size, 0);
}
void sentToClt(DataPkt& p) {
}
DataPkt recvPacket(void) {
	char Rx[100000];
	recv(ConnectionSocket, Rx, sizeof(Rx), 0);
	DataPkt p(Rx);
	return p;
}
void sendData(int VAL) {
	switch (VAL) {
	case 1:
	{
		DataPkt s;
		s.setHead(0, 1, 0);
		int size;
		s.setTBuf(NULL, size);
		sendToClt(s.getTBuf(), size);
		break;
	}
	case 2:
	{
		break;
	}
	case 3:
	{
		break;
	}
	case 4:
	{
		break;
	}
	default:
	{
		qDebug("Invalid flag parameter passed. Nothing sent, please reconfigure.");
		break;
	}
	}
}
void sendData(Courier c) {
	DataPkt p;
	std::string tmp;
	char cbuf[1000];
	
	strcpy_s(cbuf, );

	//p.setHead(COURIERDT, 0, )
}
