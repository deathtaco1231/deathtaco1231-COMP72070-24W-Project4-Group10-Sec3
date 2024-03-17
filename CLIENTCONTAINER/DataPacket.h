#pragma once
#define LOGINDT 1
#define IMGDT 2
#define PKGDT 3
#define COURIERDT 4
#define FLAGONLYDT 5
#include "AllHeaders.h"
struct Header2 {
	unsigned char DType : 4;
	unsigned char Flags : 4;
	unsigned int Datasize;
};
struct Tail2 {
	unsigned char Seqnum;
};
class DataPkt2 {
protected:
	Header2 head;
	char* TBuf;
	Tail2 tail;
public:
	DataPkt2();
	~DataPkt2();
	DataPkt2(char*);
	void setHead(unsigned char, unsigned char, unsigned int);
	void setDType(unsigned char);
	void setFlags(unsigned char);
	void setDsize(unsigned int);
	void setTBuf(char*, int&);
	char* getTBuf();
	int getDType();
	int getFlags();
	int getDSize();
	int getSeqNum();
};
int head2Size = sizeof(Header2);
int tail2Size = sizeof(Tail2);