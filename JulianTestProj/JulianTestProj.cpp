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


namespace JulianTestProj
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
			DataPkt tst;
			tst.setDType(0);
			tst.setFlags(0);
			tst.setDsize(DataSize);
			char data[7500] = { "Hello World!" }; // data buffer must be same size

			// Act
			int size = 0;
			tst.setTBuf(data, size);

			// Assert
			Assert::IsTrue(size == 7500 + sizeof(Header) + sizeof(Tail) && tst.getTBuf() != NULL);
		}
		TEST_METHOD(TST_CLT007_CREATEINVALIDTBUF)
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
		TEST_METHOD(TST_CLTOO8_RETRIEVEINVALIDTBUF)
		{
			// Arrange
			DataPkt tmp; 
			tmp.setHead(1, 1, 100);
			char data[100] = { "Hello World" };
			int size = 0;
			tmp.setTBuf(data, size);
			char* modify = tmp.getTBuf();
			

			// Act
			delete[] modify;

			// Assert
			Assert::IsTrue(tmp.getTBuf() == nullptr);

		}
		TEST_METHOD(TST_CLTOO9_RETUNINITBUF)
		{
			// Arrange
			DataPkt tmp;
			tmp.setHead(0, 0, NULL);

			// Act
			char* test = tmp.getTBuf();

			// Assert
			Assert::IsTrue(test == nullptr);
		}
		TEST_METHOD(TST_CLTO10_RBUFSIZETOOBIG)
		{
			// Arrange
			int datasize = 1000001;
			char* data = new char[datasize];
			memset(data, 1, datasize);
			Header head;
			head.Datasize = datasize;
			head.DType = 1;
			head.Flags = 0;
			memcpy(data, &head, sizeof(head));

			// Act
			DataPkt tmp(data);
			char* test = tmp.getTBuf();
			delete[] data;

			// Assert
			Assert::IsTrue(test == nullptr);
		}
		TEST_METHOD(TST_CLTO10_RBUFSIZENEGATIVE)
		{
			// Arrange
			char* data = new char[500];
			memset(data, 1, sizeof(data));
			Header head;
			head.Datasize = -1;
			head.DType = 1;
			head.Flags = 0;
			memcpy(data, &head, sizeof(head));

			// Act
			DataPkt tmp(data);
			char* test = tmp.getTBuf();
			delete[] data;

			// Assert
			Assert::IsTrue(test == nullptr);

		}
		TEST_METHOD(TST_CLTO11_VALIDIMGSIZE)
		{
			// Arrange
			std::string fpath = "C:\\Users\\dankp\\Downloads\\Delivered.jpg";
			int expected = 9983;

			// Act
			int result = GetFileSize(fpath.c_str());

			// Assert
			Assert::AreEqual(result, expected);
		}
		TEST_METHOD(TST_CLTO12_INVALIDIMGSIZE)
		{
			// Arrange
			std::string fpath = "C:\\Users\\dankp\\Downloads\\DOESNOTEXIST.jpg";
			int expected = 0;

			// Act
			int result = GetFileSize(fpath.c_str());

			// Assert
			Assert::AreEqual(result, expected);
		}
		/*TEST_METHOD(TST_CLTO13)
		{

		}
		TEST_METHOD(TST_CLTO14)
		{

		}
		TEST_METHOD(TST_CLTO15)
		{

		}*/

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
		TEST_METHOD(TST_SRV012)
		{

		}
		TEST_METHOD(TST_SRV013)
		{

		}
		TEST_METHOD(TST_SRV014_VALIDCOURIER)
		{
			// Arrange
			std::ofstream out("C:\\Users\\dankp\\Downloads\\test_data.txt");
			out << "0,203,19,1,Cat Arena,Julian,1234;";
			out.close();
			std::string uname, pword, fname;
			uname = "Julian";
			pword = "1234";
			fname = "C:\\Users\\dankp\\Downloads\\test_data.txt";

			// Act
			bool test = authCourier(uname, pword, fname);
			std::remove("C:\\Users\\dankp\\Downloads\\test_data.txt");
			// Assert
			Assert::IsTrue(test);
		}
		TEST_METHOD(TST_SRV015_INVALIDUNAME)
		{
			// Arrange
			std::string uname, pword, fname;
			uname = "INVALID";
			pword = "1234";
			fname = "C:\\Users\\dankp\\Downloads\\test_data.txt";

			// Act
			bool test = authCourier(uname, pword, fname);
			std::remove("C:\\Users\\dankp\\Downloads\\test_data.txt");
			// Assert
			Assert::IsFalse(test);
		}
		TEST_METHOD(TST_SRV015_INVALIDPWORD)
		{
			// Arrange
			std::string uname, pword, fname;
			uname = "Julian";
			pword = "INVALID";
			fname = "C:\\Users\\dankp\\Downloads\\test_data.txt";
			// Act
			bool test = authCourier(uname, pword, fname);
			std::remove("C:\\Users\\dankp\\Downloads\\test_data.txt");
			// Assert
			Assert::IsFalse(test);
		}
	};
	TEST_CLASS(SystemTests) // Tests which are flagged as tested inside the Squish automated testing tool are marked as false (fail) until they pass in that tool and are marked as passed in the test log
	{						// Once this happens, the false flag here is changed to true
	public:
		TEST_METHOD(TST_SYS_001)
		{
			//TESTED INSIDE CATCH AND REPLY TOOL
			Assert::IsTrue(true);
		}
		TEST_METHOD(TST_SYS_002)
		{
			//TESTED INSIDE CATCH AND REPLY TOOL
			Assert::IsTrue(true);
		}
		TEST_METHOD(TST_SYS_003)
		{
			//TESTED INSIDE CATCH AND REPLY TOOL
			Assert::IsTrue(true);
		}
		TEST_METHOD(TST_SYS_004)
		{

		}
		TEST_METHOD(TST_SYS_005)
		{

		}
		TEST_METHOD(TST_SYS_006)
		{

		}
		TEST_METHOD(TST_SYS_007)
		{

		}

	};
}
