#include "DataPacket.h"
DataPkt::DataPkt() {
	memset(&this->head, 0, headSize);
	this->TBuf = nullptr;
	memset(&this->tail, 0, tailSize);
}
DataPkt::DataPkt(char* buf) {
	memcpy(&head, buf, sizeof(head));
	TBuf = new char[head.Datasize];
	memcpy(TBuf, buf + sizeof(head), head.Datasize);
	memcpy(&tail, buf + sizeof(head) + head.Datasize, sizeof(tail));
}
void DataPkt::setHead(unsigned char dt, unsigned char fl, unsigned int size) {
	this->head.DType = dt;
	this->head.Flags = fl;
	this->head.Datasize = size;
}
void DataPkt::setDType(unsigned char a) {
	this->head.DType = a;
}
void DataPkt::setFlags(unsigned char a) {
	this->head.Flags = a;
}
void DataPkt::setDsize(unsigned int a) {
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