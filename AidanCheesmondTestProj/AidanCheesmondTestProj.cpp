#include "pch.h"
#include "CppUnitTest.h"

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
extern std::vector<std::string> provvect;


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AidanCheesmondTestProj
{
	TEST_CLASS(AidanCheesmondTestProj)
	{
	public:
		
        TEST_METHOD(SRV_21_DefaultConstructor)
        {
            // Arrange
            Address address;

            // Act
            std::string city = address.getCity();
            std::string province = address.getProvince();
            std::string stAddr = address.getstAddr();
            int unitNo = address.getUnitNo();

            // Assert
            Assert::AreEqual(std::string("Empty"), city);
            Assert::AreEqual(std::string("Empty"), province);
            Assert::AreEqual(std::string("Empty, Empty, Empty"), stAddr);
            Assert::AreEqual(0, unitNo);
        }

        TEST_METHOD(SRV_21_ParameterizedConstructor)
        {
            // Arrange
            Address address("123 Main St", "Toronto", "ON");

            // Act
            std::string city = address.getCity();
            std::string province = address.getProvince();
            std::string stAddr = address.getstAddr();
            int unitNo = address.getUnitNo();

            // Assert
            Assert::AreEqual(std::string("Toronto"), city);
            Assert::AreEqual(std::string("ON"), province);
            Assert::AreEqual(std::string("123 Main St, Toronto, ON"), stAddr);
            Assert::AreEqual(0, unitNo);
        }

        TEST_METHOD(SRV_21_FullConstructor)
        {
            // Arrange
            Address address("123 Main St", "Toronto", "ON", 4);

            // Act
            std::string city = address.getCity();
            std::string province = address.getProvince();
            std::string stAddr = address.getstAddr();
            int unitNo = address.getUnitNo();

            // Assert
            Assert::AreEqual(std::string("Toronto"), city);
            Assert::AreEqual(std::string("ON"), province);
            Assert::AreEqual(std::string("123 Main St Unit #4, Toronto, ON"), stAddr);
            Assert::AreEqual(4, unitNo);
        }

        TEST_METHOD(SRV_21_GetOnlySt)
        {
            // Arrange
            Address address("123 Main St", "Toronto", "ON", 4);

            // Act
            std::string onlySt = address.getOnlySt();

            // Assert
            Assert::AreEqual(std::string("123 Main St"), onlySt);
        }

        TEST_METHOD(SRV_21_SetProvVectorTest)
        {
            //// Arrange
            //std::string testFilePath = "testProvinces.txt";
            //std::vector<std::string> expectedProvinces = { "Alberta", "British Columbia", "Manitoba" };
            //std::vector<std::string> actualProvinces;

            //// Create a test file with expected provinces
            //std::ofstream testFile(testFilePath);
            //for (const auto& province : expectedProvinces) {
            //    testFile << province << std::endl;
            //}
            //testFile.close();

            // Act
            setProvVector(provvect);

            //// Assert
            //Assert::AreEqual(expectedProvinces.size(), actualProvinces.size(), L"The size of the vector should match the number of provinces in the test file.");
            //for (size_t i = 0; i < expectedProvinces.size(); ++i) {
            //    Assert::AreEqual(expectedProvinces[i].c_str(), actualProvinces[i].c_str(), L"Each province in the vector should match the corresponding line in the test file.");
            //}

            //// Cleanup
            //std::remove(testFilePath.c_str());
        }

	};
}
