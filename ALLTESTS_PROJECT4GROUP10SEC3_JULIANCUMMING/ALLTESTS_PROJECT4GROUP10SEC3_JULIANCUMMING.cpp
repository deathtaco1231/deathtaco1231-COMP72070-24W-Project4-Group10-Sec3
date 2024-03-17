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
	TEST_CLASS(UnitTests)
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
	};
}
