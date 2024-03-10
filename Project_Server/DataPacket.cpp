#include "DataPacket.h"
DataPkt::DataPkt() {
	memset(&this->head, 0, headSize);
	this->TBuf = nullptr;
	memset(&this->tail, 0, tailSize);
}
DataPkt::DataPkt(char* buf) {

}
void DataPkt::setHead(unsigned char dt, unsigned char fl, short unsigned int size) {
	this->head.DType = dt;
	this->head.Flags = fl;
	this->head.Datasize = size;
}
//void DataPkt::setSrc(unsigned char a) {
//	this->head.Src = a;
//}
//void DataPkt::setDst(unsigned char a) {
//	this->head.Dst = a;
//}
void DataPkt::setDType(unsigned char a) {
	this->head.DType = a;
}
void DataPkt::setFlags(unsigned char a) {
	this->head.Flags = a;
}
void DataPkt::setDsize(unsigned short int a) {
	this->head.Datasize = a;
}
char* DataPkt::setTBuf(char* data, int& size) {
	if (TBuf)
		delete TBuf;
	size = headSize + head.Datasize + tailSize;
	TBuf = new char[size];
	memcpy(TBuf, &head, headSize);
	memcpy(TBuf + headSize, data, head.Datasize);
	memcpy(TBuf + headSize + head.Datasize, &tail, tailSize);
	return TBuf;
}