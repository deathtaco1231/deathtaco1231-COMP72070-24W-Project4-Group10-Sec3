#include "DataPacket.h"
DataPkt2::DataPkt2() {
	memset(&this->head, 0, head2Size);
	this->TBuf = nullptr;
	memset(&this->tail, 0, tail2Size);
}
DataPkt2::DataPkt2(char* buf) {
	memcpy(&head, buf, sizeof(head));
	TBuf = new char[head.Datasize];
	memcpy(TBuf, buf + sizeof(head), head.Datasize);
	memcpy(&tail, buf + sizeof(head) + head.Datasize, sizeof(tail));
}
void DataPkt2::setHead(unsigned char dt, unsigned char fl, unsigned int size) {
	this->head.DType = dt;
	this->head.Flags = fl;
	this->head.Datasize = size;
}
void DataPkt2::setDType(unsigned char a) {
	this->head.DType = a;
}
void DataPkt2::setFlags(unsigned char a) {
	this->head.Flags = a;
}
void DataPkt2::setDsize(unsigned int a) {
	this->head.Datasize = a;
}
void DataPkt2::setTBuf(char* data, int& size) {
	if (TBuf)
		delete TBuf;
	size = head2Size + head.Datasize + tail2Size;
	TBuf = new char[size];
	memcpy(TBuf, &head, head2Size);
	if (head.Datasize != 0)
		memcpy(TBuf + head2Size, data, head.Datasize);
	memcpy(TBuf + head2Size + head.Datasize, &tail, tail2Size);
}
char* DataPkt2::getTBuf(void) {
	return this->TBuf;
}
DataPkt2::~DataPkt2() {
	if (TBuf)
		delete[] TBuf;
}
int DataPkt2::getDType(void) {
	return (int)this->head.DType;
}
int DataPkt2::getFlags(void) {
	return (int)this->head.Flags;
}
int DataPkt2::getDSize(void) {
	return this->head.Datasize;
}
int DataPkt2::getSeqNum(void) {
	return (int)this->tail.Seqnum;
}