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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AidanNickersonTestProj
{
	TEST_CLASS(AidanNickersonTestProj_Date_UnitTests)
	{
	public:
		
        TEST_METHOD(TestDefaultConstructor)
        {
            date d;
            Assert::AreEqual(0, d.getyear(), L"Default constructor year should be 0");
            Assert::AreEqual(0, d.getmonth(), L"Default constructor month should be 0");
            Assert::AreEqual(0, d.getday(), L"Default constructor day should be 0");
        }

        TEST_METHOD(TestParameterizedConstructor)
        {
            date d(18, 3, 2024);
            Assert::AreEqual(2024, d.getyear(), L"Parameterized constructor year should be 2024");
            Assert::AreEqual(3, d.getmonth(), L"Parameterized constructor month should be 3");
            Assert::AreEqual(18, d.getday(), L"Parameterized constructor day should be 18");
        }

        TEST_METHOD(TestValidDate)
        {
            date d(18, 3, 2024);
            Assert::IsTrue(d.valid(), L"Valid date should return true");
        }

        TEST_METHOD(TestInvalidDate)
        {
            date d(30, 2, 2024);
            Assert::IsFalse(d.valid(), L"Invalid date should return false");
        }

        TEST_METHOD(TestSettersAndGetters)
        {
            date d;
            d.setyear(2024);
            d.setmonth(3);
            d.setday(18);
            Assert::AreEqual(2024, d.getyear(), L"Year should be 2024");
            Assert::AreEqual(3, d.getmonth(), L"Month should be 3");
            Assert::AreEqual(18, d.getday(), L"Day should be 18");
        }

        TEST_METHOD(TESTLONGDATE)
        {
            // Create a date object with known values
            date testDate(15, 3, 2024); // Example date: March 15, 2024

            // Convert the date object to an int using long_date()
            int dateInt = long_date(testDate);

            // Construct the expected int value (e.g., 20240315)
            int expectedInt = 20240315;

            // Assert that the converted int matches the expected value
            Assert::AreEqual(expectedInt, dateInt);

        }

        TEST_METHOD(TESTLONGDATE_INVALID)
        {
            date d(15, 13, 2024);

            int dateint = long_date(d);

            int dateisntint = 20241315;

            Assert::AreNotEqual(dateisntint, dateint);
        }

        TEST_METHOD(DATETTOSTRING)
        {
            date d(15, 3, 2024);

            std::string datestring = d.datetos();

            Assert::AreEqual(std::string("2024/3/15"), datestring);


        }

        TEST_METHOD(ValidDateOutputTest)
        {
            // Create a valid date2 object
            date validDate(15, 3, 2024);

            // Output the date to a stringstream
            std::stringstream ss;
            ss << validDate;

            // Verify the output
            Assert::AreEqual(std::string(" 20240315 "), ss.str());
        }

        TEST_METHOD(InvalidDateOutputTest)
        {
            // Create a valid date2 object
            date invalidDate(30, 2, 2024);

            // Output the date to a stringstream
            std::stringstream ss;
            ss << invalidDate;

            // Verify the output
            Assert::AreEqual(std::string(" invalid date "), ss.str());
        }



	};

}
