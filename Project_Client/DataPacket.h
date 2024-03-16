 #pragma once
#define LOGINDT 1
#define IMGDT 2
#define PKGDT 3
#define COURIERDT 4
#define FLAGONLYDT 5
#include "AllHeaders.h"
struct Header {
	unsigned char DType : 4;
	unsigned char Flags : 4;
	unsigned int Datasize;
};
struct Tail {
	unsigned char Seqnum;
};
class DataPkt {
protected:
	Header head;
	char* TBuf;
	Tail tail;
public:
	DataPkt();
	~DataPkt();
	DataPkt(char*);
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
int headSize = sizeof(Header);
int tailSize = sizeof(Tail);