#include "DataPacket.h"
DataPkt::DataPkt() {
	memset(&this->head, 0, headSize);
	this->TBuf = nullptr;
	memset(&this->tail, 0, tailSize);
}
DataPkt::DataPkt(char* buf) {
	memcpy(&head, buf, sizeof(head));
	if (head.Datasize < 0 || head.Datasize > 1000000)
		TBuf = nullptr;
	else {
		TBuf = new char[head.Datasize];
		memcpy(TBuf, buf + sizeof(head), head.Datasize);
	}
	if (head.Datasize > 0 && head.Datasize < 1000000)
		memcpy(&tail, buf + sizeof(head) + head.Datasize, sizeof(tail));
	else
		memset(&tail, 0, sizeof(tail));
}
void DataPkt::setHead(unsigned char dt, unsigned char fl, unsigned int size) {
	if (dt <= 15 && dt >= 0)
		this->head.DType = dt;
	else
		this->head.DType = 0;
	if (fl <= 15 && fl >= 0)
		this->head.Flags = fl;
	else
		this->head.Flags = 0;
	if (size <= 1000000 && size >= 0)
		this->head.Datasize = size;
	else
		this->head.Datasize = 0;
}
void DataPkt::setDType(unsigned char a) {
	if (a >= 0 && a <= 15)
		this->head.DType = a;
}
void DataPkt::setFlags(unsigned char a) {
	if (a >= 0 && a <= 15)
		this->head.Flags = a;
}
void DataPkt::setDsize(unsigned int a) {
	if (a >= 0 && a <= 1000000)
		this->head.Datasize = a;
}
void DataPkt::setTBuf(char* data, int& size) {
	if (TBuf)
		delete TBuf;
	size = headSize + head.Datasize + tailSize;
	TBuf = new char[size];
	memcpy(TBuf, &head, headSize);
	if (head.Datasize != 0)
		memcpy(TBuf + headSize, data, head.Datasize);
	memcpy(TBuf + headSize + head.Datasize, &tail, tailSize);
}
char* DataPkt::getTBuf(void) {
	Header h;
	memcpy(&h, &this->TBuf, sizeof(head));
	if (h.Datasize != this->head.Datasize || h.DType != this->head.DType || h.Flags != this->head.Flags)
		this->TBuf = nullptr;
	return this->TBuf;
}
DataPkt::~DataPkt() {
	if (TBuf)
		delete[] TBuf;
}
int DataPkt::getDType(void) {
	return (int)this->head.DType;
}
int DataPkt::getFlags(void) {
	return (int)this->head.Flags;
}
int DataPkt::getDSize(void) {
	return this->head.Datasize;
}
int DataPkt::getSeqNum(void) {
	return (int)this->tail.Seqnum;
}