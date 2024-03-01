#pragma once
#include "AllHeaders.h"
struct Header {
	unsigned char Src : 4;
	unsigned char Dst : 4;
	unsigned char DType : 4;
	unsigned char Flags : 4;
	short unsigned int Datasize;
};
struct Tail {
	unsigned char Seqnum;
};
class DataPkt {
protected:
	Header head;
	char* TBuf;
	Tail tail;
	DataPkt();
public:
	DataPkt(char*);
	void setHead(unsigned char, unsigned char, unsigned char, unsigned char, short unsigned int);
	void setSrc(unsigned char);
	void setDst(unsigned char);
	void setDType(unsigned char);
	void setFlags(unsigned char);
	void setDsize(unsigned short int);
};
int headSize = sizeof(Header);
int tailSize = sizeof(Tail);