#pragma once
#include "AllHeaders.h"

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

