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
            Assert::AreEqual(std::string("Toronto"), city);
            Assert::AreEqual(std::string("ON"), province);
            Assert::AreEqual(std::string("123 Main St Unit #4, Toronto, ON"), stAddr);
            Assert::AreEqual(4, unitNo);
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

        //TEST_METHOD(SRV_25_SetProvVectorTest)
        //{
        //    /* Arrange */
        //    std::string testFilePath = "C:\\Users\Aeche\Downloads\provinces.txt";
        //    std::vector<std::string> expectedProvinces = { "Alberta", "British Columbia", "Manitoba" };
        //    std::vector<std::string> actualProvinces;

        //    /* Create a test file with expected provinces */
        //    std::ofstream testFile(testFilePath);
        //    for (const auto& province : expectedProvinces) {
        //        testFile << province << std::endl;
        //    }
        //    testFile.close();

        //    /* Act */
        //    setProvVector(provvect);

        //    /* Assert */
        //    Assert::AreEqual(expectedProvinces.size(), actualProvinces.size(), "The size of the vector should match the number of provinces in the test file.");
        //    for (size_t i = 0; i < expectedProvinces.size(); ++i) {
        //        Assert::AreEqual(expectedProvinces[i].c_str(), actualProvinces[i].c_str(), "Each province in the vector should match the corresponding line in the test file.");
        //    }

        //    /* Cleanup */
        //    std::remove(testFilePath.c_str());
        //}


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
            date deliverBy;
            date createdOn;
            bool isAssigned = package.checkifassigned();

  
            // Assert
            Assert::AreEqual(std::string(""), labelImgPath);
            Assert::AreEqual(0, id); // Assuming ID defaults to 0 if not set
            Assert::AreEqual(std::string("UNNAMED"), itemName);
            Assert::AreEqual(0.0, weight);
            Assert::AreEqual(0.0, length);
            Assert::AreEqual(0.0, height);
            Assert::AreEqual(0.0, width);
            
            //Assert::IsTrue(deliverBy == date()); // Assuming date has a sensible default
            //Assert::IsTrue(createdOn == currdate); // Assuming currdate is defined
            Assert::IsFalse(isAssigned);
        }

        TEST_METHOD(ParameterizedConstructor1)
        {
            // Arrange
            std::string expectedLabelImgPath = "DeliveredPackage.jpg";
            int expectedID = 123;
            std::string expectedItemName = "Item";
            double expectedWeight = 10.0;
            double expectedLength = 20.0;
            double expectedWidth = 30.0;
            double expectedHeight = 40.0;
            date expectedDeliverBy; // Assuming date is properly initialized

            // Act
            Package package(expectedLabelImgPath, expectedID, expectedItemName, expectedWeight, expectedLength, expectedWidth, expectedHeight, expectedDeliverBy);

            
            // Assert
            Assert::AreEqual(expectedLabelImgPath, package.getImgPath());
            Assert::AreEqual(expectedID, package.getID());
            Assert::AreEqual(expectedItemName, package.getItem());
            Assert::AreEqual(expectedWeight, package.getWeight());
            Assert::AreEqual(expectedLength, package.getLength());
            Assert::AreEqual(expectedHeight, package.getHeight());
            Assert::AreEqual(expectedWidth, package.getWidth());
           /* Assert::IsTrue(expectedDeliverBy == package.getDeliverBy()); */
          /*  Assert::IsTrue(currdate == package.getCreationDate());*/
            /*Assert::IsFalse(package.checkifassigned());*/
        }

        TEST_METHOD(InitPkgVectTest)
        {
            // Arrange
            std::ofstream out("test_data.txt");
            out << "DeliveredPackage.jpg,2,200 Old Carriage Drive,Kitchener,Ontario,Lmao,14.3,86,44.62,3,6,3,2025,true\n";
            out.close();

            // Act
            bool result = initPkgVect();

           //  Assert
            Assert::IsTrue(result);
            Assert::IsTrue(allPkgs.size() > 0);

           //  Cleanup
            std::remove("packages.txt");
        }

        TEST_METHOD(ReadPkgTest)
        {
            bool worked = false;
            // Arrange
            std::ifstream inFile("test_data.txt");
            if (inFile.is_open()) {
                // Act
                Package p = readPkg(inFile);
                Package p2;
                if (p.toString() == p2.toString())
                    worked = true;
            }

            // Assert
            Assert::IsTrue(worked);
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
