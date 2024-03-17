#include "pch.h"
#include "CppUnitTest.h"

#include "../CLIENTCONTAINER/Address.cpp"
#include "../CLIENTCONTAINER/DataPkt.cpp"
#include "../CLIENTCONTAINER/Date.cpp"
#include "../CLIENTCONTAINER/Networking.cpp"
#include "../CLIENTCONTAINER/Package.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
extern SOCKET ServerSocket, ConnectionSocket;
extern int headSize;
extern int tailSize;
extern std::vector<Package> allPkgs;
extern Package tmpPkg;
extern bool isDel;

namespace ALLTESTSPROJECT4GROUP10SEC3JULIANCUMMING
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
		}
	};
}
