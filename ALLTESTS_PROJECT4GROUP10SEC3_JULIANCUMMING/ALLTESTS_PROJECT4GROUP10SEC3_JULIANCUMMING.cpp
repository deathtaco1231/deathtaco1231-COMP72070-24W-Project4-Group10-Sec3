#include "pch.h"
#include "CppUnitTest.h"
// Server containters remain original class names
#include "../SERVERCONTAINER/Address.cpp"
#include "../SERVERCONTAINER/DataPkt.cpp"
#include "../SERVERCONTAINER/Date.cpp"
#include "../SERVERCONTAINER/Networking.cpp"
#include "../SERVERCONTAINER/Package.cpp"
#include "../SERVERCONTAINER/Person.cpp"
#include "../SERVERCONTAINER/Courier.cpp"
// Client container classes are marked with a '2' to avoid duplicity
#include "../CLIENTCONTAINER/Address.cpp"
#include "../CLIENTCONTAINER/DataPkt.cpp"
#include "../CLIENTCONTAINER/Date.cpp"
#include "../CLIENTCONTAINER/Networking.cpp"
#include "../CLIENTCONTAINER/Package.cpp"
#include "../CLIENTCONTAINER/Person.cpp"
#include "../CLIENTCONTAINER/Courier.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
extern SOCKET ServerSocket, ConnectionSocket;
extern int headSize;
extern int tailSize;
extern std::vector<Package2> allPkgs2;
extern std::vector<Package> allPkgs;
extern Courier currCourier;
extern Package tmpPkg;
extern bool isDel;

namespace ALLTESTSPROJECT4GROUP10SEC3JULIANCUMMING
{
	TEST_CLASS(ClientUnitTests)
	{
	public:
		
		TEST_METHOD(TST_CLT001_SMALLDATASIZE)
		{
			// Arrange
			struct Header goodhead;
			goodhead.Datasize = sizeof(Package); // Common data size (many packages are transferred under normal use)
			goodhead.DType = 10;
			goodhead.Flags = 1; // Standard type and flags

			// Act
			DataPkt tst;
			tst.setHead(10, 1, sizeof(Package));
			
			// Assert
			Assert::IsTrue(tst.getDSize() == goodhead.Datasize && tst.getFlags() == goodhead.Flags && tst.getDType() == goodhead.DType);
		}
		TEST_METHOD(TST_CLT001_LARGEDATASIZE)
		{
			// Arrange
			int ImgSize = 150000; // Expected average size for an image transfer, should be within the limits of the packet structure to handle
			struct Header goodhead;
			goodhead.Datasize = ImgSize; // Common data size (many packages are transferred under normal use)
			goodhead.DType = 5;
			goodhead.Flags = 3; // Standard type and flags

			// Act
			DataPkt tst;
			tst.setHead(5, 3, ImgSize);

			// Assert
			Assert::IsTrue(tst.getDSize() == goodhead.Datasize && tst.getFlags() == goodhead.Flags && tst.getDType() == goodhead.DType);
		}
		TEST_METHOD(TST_CLT002_INVALIDFLAGANDDTYPE)
		{
			// Arrange
			int ImgSize = 150000; // Expected average size for an image transfer, should be within the limits of the packet structure to handle
			struct Header goodhead;
			goodhead.Datasize = ImgSize; // Common data size (many packages are transferred under normal use)
			goodhead.DType = 0;
			goodhead.Flags = 0; // We expect both to remain 0 if function operates correctly

			// Act
			DataPkt tst;
			tst.setHead(16, -1, ImgSize); // DType too high, flags too low

			// Assert
			Assert::IsTrue(tst.getFlags() == goodhead.Flags && tst.getDType() == goodhead.DType);
		}
		TEST_METHOD(TST_CLT002_DSIZETOOLARGE)
		{
			// Arrange
			int ImgSize = 1000001; // More than 1 million
			struct Header goodhead;
			goodhead.Datasize = 0; // We expect it to remain 0
			goodhead.DType = 5;
			goodhead.Flags = 3; // Standard type and flags

			// Act
			DataPkt tst;
			tst.setHead(5, 3, ImgSize);

			// Assert
			Assert::IsTrue(tst.getDSize() == goodhead.Datasize);
		}
		TEST_METHOD(TST_CLT002_NEGATIVEDSIZE)
		{
			// Arrange
			int ImgSize = -1; // Data size below 0, invalid
			struct Header goodhead;
			goodhead.Datasize = 0; // We expect it to remain 0
			goodhead.DType = 5;
			goodhead.Flags = 3; // Standard type and flags

			// Act
			DataPkt tst;
			tst.setHead(5, 3, ImgSize);

			// Assert
			Assert::IsTrue(tst.getDSize() == goodhead.Datasize);
		}
		TEST_METHOD(TST_CLT003_DSIZESETTER)
		{
			// Arrange
			struct Header goodhead;
			goodhead.Datasize = 0; // We expect it to remain 0
			goodhead.DType = 0;
			goodhead.Flags = 0; // Standard type and flags

			// Act
			DataPkt tst1; // Will be too HIGH
			tst1.setDsize(1000001);
			DataPkt tst2; // Will be too LOW
			tst2.setDsize(-1);
			

			// Assert
			Assert::IsTrue(tst1.getDSize() == goodhead.Datasize && tst2.getDSize() == goodhead.Datasize);
		}
		TEST_METHOD(TST_CLT004_FLAGSETTER)
		{
			// Arrange
			struct Header goodhead;
			goodhead.Datasize = 0;
			goodhead.DType = 0;
			goodhead.Flags = 0; // Should remain 0 as per requirements

			// Act
			DataPkt tst1; // Will be too HIGH
			tst1.setFlags(16);
			DataPkt tst2; // Will be too LOW
			tst2.setFlags(-1);

			// Assert
			Assert::IsTrue(tst1.getFlags() == goodhead.Flags && tst2.getFlags() == goodhead.Flags);
		}
		TEST_METHOD(TST_CLT005_DTYPESETTER)
		{
			// Arrange
			struct Header goodhead;
			goodhead.Datasize = 0; 
			goodhead.DType = 0; // Should remain 0 as per requirements
			goodhead.Flags = 0; 

			// Act
			DataPkt tst1; // Will be too HIGH
			tst1.setDType(16);
			DataPkt tst2; // Will be too LOW
			tst2.setDType(-1);

			// Assert
			Assert::IsTrue(tst1.getDSize() == goodhead.Datasize && tst2.getDSize() == goodhead.Datasize);
		}
		TEST_METHOD(TST_CLT006_VALIDTBUF)
		{
			// Arrange
			int DataSize = 7500; // Arbitrary Valid Number
			DataPkt tmp;
			tmp.setHead(0, 0, DataSize);
			char data[7500] = { "Hello World!" }; // data buffer must be same size

			// Act
			int size = 0;
			tmp.setTBuf(data, size);

			// Assert
			Assert::IsTrue(size == 7500 + sizeof(Header) + sizeof(Tail) && tmp.getTBuf() != NULL);
		}
		TEST_METHOD(TST_CLT007_INVALIDTBUF)
		{
			// Arrange
			DataPkt tmp;
			tmp.setHead(0, 0, NULL); // Passing in NULL data stream
			char data[7500] = { "Hello World!" }; // data buffer must be same size

			// Act
			int size = 0;
			tmp.setTBuf(data, size);

			// Assert
			Assert::IsTrue(size == sizeof(Header) + sizeof(Tail) && tmp.getTBuf() != NULL); // Expected to create default packet with default info so SOMETHING is sent 
		}
		
	};
	TEST_CLASS(ServerUnitTests)
	{
	public:

		TEST_METHOD(TST_SRV009_FILESIZEVALIDPATH)
		{
			// Arrange
			std::string tstpath = "C:\\Users\\dankp\\Downloads\\Label2.jpg";
			int ACTSIZE = 13143; // verified actual size in bytes
			
			// Act
			int tstsize = GetFileSize(tstpath.c_str());

			// Assert
			Assert::AreEqual(ACTSIZE, tstsize);
		}
		TEST_METHOD(TST_SRV010_FILESIZEINVALIDPATH)
		{
			// Arrange
			std::string tstpath = "C:\\Users\\dankp\\Downloads\\DOESNOTEXIST.jpg"; // Invalid file
			int ACTSIZE = 0;

			// Act
			int tstsize = GetFileSize(tstpath.c_str());

			// Assert
			Assert::AreEqual(ACTSIZE, tstsize);
		}
		TEST_METHOD(TST_SRV011_INITWITHPORTTAKEN)
		{
			// Arrange
			SOCKET tmpSocket; // This socket will act as an app running on the server system which has taken the port that the server intends to use.
			WSADATA wsaData;
			WSAStartup(MAKEWORD(2, 2), &wsaData);
			tmpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			sockaddr_in SvrAddr;
			SvrAddr.sin_family = AF_INET;
			SvrAddr.sin_addr.s_addr = INADDR_ANY;
			SvrAddr.sin_port = htons(27000);
			bind(tmpSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr));

			// Act
			bool isBound = true;
			isBound = initSrvSocket(); // if server socket cannot be initalized, will return false;
			WSACleanup();

			// Assert
			Assert::IsFalse(isBound);
		}
		
	};
}
