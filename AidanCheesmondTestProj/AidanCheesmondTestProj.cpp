#include "pch.h"
#include "CppUnitTest.h"

#include "../SERVERCONTAINER/Address.cpp"
#include "../SERVERCONTAINER/DataPkt.cpp"
#include "../SERVERCONTAINER/Date.cpp"
#include "../SERVERCONTAINER/Networking.cpp"
#include "../SERVERCONTAINER/Package.cpp"
#include "../SERVERCONTAINER/Person.cpp"
#include "../SERVERCONTAINER/Courier.cpp"
#include "../SERVERCONTAINER/Order.cpp"
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
		// Address Tests
        TEST_METHOD(SRV_21_DefaultConstructor)
        {
            // Arrange
            Address address;

            // Act
            std::string city = address.getCity();
            std::string province = address.getProvince();
            std::string stAddr = address.getstAddr();
            int unitNo = address.getUnitNo();
            std::string actual = city + ", " + province + ", " + stAddr + ", " + std::to_string(unitNo);

            // Assert
            std::string expected = "Empty, Empty, Empty, Empty, Empty, 0";
            Assert::AreEqual(expected, actual);
        }



        TEST_METHOD(SRV_22_ParameterizedConstructor)
        {
            // Arrange
            Address address("123 Main St", "Toronto", "ON");

            // Act
            std::string stAddr = address.getstAddr();

            // Assert
            Assert::AreEqual(std::string("123 Main St, Toronto, ON"), stAddr);
        }


        TEST_METHOD(SRV_23_FullConstructor)
        {
            // Arrange
            Address address("123 Main St", "Toronto", "ON", 4);

            // Act
            std::string city = address.getCity();
            std::string province = address.getProvince();
            std::string stAddr = address.getstAddr();
            int unitNo = address.getUnitNo();

            // Assert
            Assert::IsTrue(city == "Toronto" &&
                province == "ON" &&
                stAddr == "123 Main St Unit #4, Toronto, ON" &&
                unitNo == 4);
        }

        TEST_METHOD(SRV_24_GetOnlySt)
        {
            // Arrange
            Address address("123 Main St", "Toronto", "ON", 4);

            // Act
            std::string onlySt = address.getOnlySt();

            // Assert
            Assert::AreEqual(std::string("123 Main St"), onlySt);
        }

        TEST_METHOD(SRV_25_SetProvVectorTest)
        {
            // Arrange
            std::vector<std::string> expectedProvinces = { "Alberta", "British Columbia", "Manitoba" };
            std::vector<std::string> actualProvinces;

            //Act
            setProvVector(provvect, "C:\\Users\\dankp\\Downloads\\provinces.txt");

            // Assert
            Assert::AreEqual(expectedProvinces.size(), provvect.size());
        }



        // Package Tests
        TEST_METHOD(SRV_26_Package)
        {
            // Arrange
            Package package;

            // Act
            std::string labelImgPath = package.getImgPath();
            int id = package.getID();
            std::string itemName = package.getItem();
            double weight = 0;
            double length = package.getLength();
            double height = package.getHeight();
            double width = package.getWidth();
            bool isAssigned = package.checkifassigned();

            // Assert
            Assert::IsTrue(labelImgPath == "EMPTY" &&
                id == 0 && itemName == "UNNAMED" &&
                weight == 0.0 && length == 0.0 &&
                height == 0.0 && width == 0.0 /*&&
                deliverBy == date() && createdOn == currdate &&
                !isAssigned*/);
        }


        TEST_METHOD(ParameterizedConstructor1)
        {
            // Arrange
            std::string expectedLabelImgPath = "DeliveredPackage.jpg";
            int expectedID = 123;
            std::string expectedItemName = "Item";
            double expectedWeight = 10.000000000000000;
            double expectedLength = 20.000000000000000;
            double expectedWidth = 30.000000000000000;
            double expectedHeight = 40.000000000000000;
            date expectedDeliverBy; // Assuming date is properly initialized

            // Act
            Package package(expectedLabelImgPath, expectedID, expectedItemName, expectedWeight, expectedLength, expectedWidth, expectedHeight, expectedDeliverBy);

            // Assert
            Assert::IsTrue(expectedLabelImgPath == package.getImgPath() &&
                expectedID == package.getID() &&
                expectedItemName == package.getItem() &&
                expectedWeight == package.getWeight() &&
                expectedLength == package.getLength() &&
                expectedHeight == package.getHeight() &&
                expectedWidth == package.getWidth() /*&&
                expectedDeliverBy == package.getDeliverBy() &&
                currdate == package.getCreationDate() &&
                !package.checkifassigned()*/);
        }

        TEST_METHOD(InitPkgVectTest)
        {
            // Arrange
            std::ofstream out("C:\\Users\\dankp\\Downloads\\test.txt");
            out << "DeliveredPackage.jpg,2,200 Old Carriage Drive,Kitchener,Ontario,Lmao,14.3,86,44.62,3,6,3,2025,true";
            out.close();

            // Act
            bool result = initPkgVect("C:\\Users\\dankp\\Downloads\\test.txt");
            std::remove("C:\\Users\\dankp\\Downloads\\test.txt");

           //  Assert
            Assert::IsTrue(result);
            Assert::IsTrue(allPkgs.size() > 0);
        }

        TEST_METHOD(ReadPkgTest)
        {
            // Arrange
            std::ofstream out("C:\\Users\\dankp\\Downloads\\test_data.txt");
            out << "EMPTY,0,Empty,Empty,Empty,UNNAMED,0,0,0,0,0,0,0,No";
            out.close();
            bool worked = false;
            std::ifstream inFile("C:\\Users\\dankp\\Downloads\\test_data.txt");
            if (inFile.is_open()) {
                // Act
                Package p = readPkg(inFile);
                Package p2;
                if (p.toString() == p2.toString())
                    worked = true;
            }
            if (inFile.is_open())
                inFile.close();
            std::remove("C:\\Users\\dankp\\Downloads\\test_data.txt");
            // Assert
            Assert::IsTrue(worked);
            
            //bool worked = false;
            //// Arrange
            //std::ifstream inFile("test_data.txt");
            //if (inFile.is_open()) {
            //    // Act
            //    Package p = readPkg(inFile);
            //    Package p2;
            //    if (p.toString() == p2.toString())
            //        worked = true;
            //}

            //// Assert
            //Assert::IsTrue(worked);
        }

        TEST_METHOD(ToStringTest)
        {
            // Arrange
            Package p;
            p.setID(123);
            p.setItem("Item");
            p.setWeight(10.5);
            p.setLength(15.5);
            p.setWidth(20.5);
            p.setHeight(25.5);
            p.setDeliverBy(date(1, 1, 2024));
            p.setAssigned();

            // Act
            std::string result = p.toString();

            // Assert
            std::string expected = "123\tItem\tYes\t" + p.getCreationDate().datetos() + "\t" + p.getDeliverBy().datetos();
            Assert::AreEqual(expected, result);
        }

	};
}
