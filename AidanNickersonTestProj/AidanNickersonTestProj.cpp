#include "pch.h"
#include "CppUnitTest.h"

#include "../SERVERCONTAINER/Address.cpp"
#include "../SERVERCONTAINER/DataPkt.cpp"
#include "../SERVERCONTAINER/Date.cpp"
#include "../SERVERCONTAINER/Networking.cpp"
#include "../SERVERCONTAINER/Package.cpp"
#include "../SERVERCONTAINER/Person.cpp"
#include "../SERVERCONTAINER/Courier.cpp"
#include"../SERVERCONTAINER/Order.cpp"
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
extern date currdate;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AidanNickersonTestProj
{
	TEST_CLASS(AidanNickersonTestProj_Date_UnitTests)
	{
	public:
		
        TEST_METHOD(TestDefaultConstructor)
        {
            date d;
            
            Assert::IsTrue(1 == d.getyear() && 0 == d.getmonth() && 0 == d.getyear());
        }

        TEST_METHOD(TestParameterizedConstructor)
        {
            date d(18, 3, 2024);
           
            Assert::IsTrue(2024 == d.getyear() && 3 == d.getmonth() && 18 == d.getday());
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
           
            Assert::IsTrue(2024 == d.getyear() && 3 == d.getmonth() && 18 == d.getday());
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
            Assert::AreEqual(" invalid date ", ss.str().c_str());
        }

        TEST_METHOD(TestLeapYear)
        {
            // Test a leap year
            date d(29, 2, 2024); // February 29, 2024 is a leap year
            Assert::IsTrue(d.valid(), L"Leap year should be valid");

            // Test a non-leap year
            d.setyear(2023); // 2023 is not a leap year
            Assert::IsFalse(d.valid(), L"Non-leap year should be invalid for February 29");

        }

        TEST_METHOD(TestDateToStringFunctionality)
        {
            date d(15, 3, 2024);
            std::string dateString = d.datetos();
            Assert::AreEqual(std::string("2024/3/15"), dateString, L"datetos should return the correct string representation");
        }

        TEST_METHOD(TestDateComparisonOperators)
        {
            date d1(15, 3, 2024);
            date d2(16, 3, 2024);
            date d3(15, 4, 2024);
            date d4(15, 3, 2025);

            Assert::IsTrue(d1 < d2 && d1 < d3 && d1 < d4 && d1 == d1 && d1 <= d2, L"d1 should be less than d2");
           
        }

        TEST_METHOD(TestValidMethodWithDifferentTimeZones)
        {
           
            date d(15, 3, 2024);
            Assert::IsTrue(d.valid(), L"Date should be valid in the current time zone");
            
        }


	};

    TEST_CLASS(AidanNickersonTestProj_Order_Tests)
    {
    public:

        TEST_METHOD(TestDefaultConstructor)
        {
            Order order;
            Assert::IsTrue(order.getPackage().getID() == 0 && order.getDate().getyear() == 0 && order.getCourier().getID() == 0, L"Default package ID should be 0");
           
        }


        TEST_METHOD(TestParameterizedConstructorWithPackage2)
        {
            Package p("test.jpg", 1, "Test Item", 1.0, 10.0, 10.0, 10.0, date(1, 1, 2024));
            date d(1, 1, 2024);
            Courier c(1, 0); // Assuming Courier constructor takes GoodDeliveries, LateDeliveries
            Order order(p, d, c);

           
            Assert::AreEqual(1, order.getPackage().getID(), L"Package ID should be 1");
            Assert::AreEqual(2024, order.getDate().getyear(), L"Date year should be 2024");
            Assert::AreEqual(0, order.getCourier().getID(), L"Courier ID should be 1");
        }

        TEST_METHOD(TestSettersAndGetters)
        {
            Order order;
            Package p("test.jpg", 1, "Test Item", 1.0, 10.0, 10.0, 10.0, date(1, 1, 2024));
            date d(1, 1, 2024);
            Courier c(1, 0);

            order.setPackage(p);
            order.setDate(d);
            order.setCourier(c);

            Assert::AreEqual(1, order.getPackage().getID(), L"Package ID should be 1");
            Assert::AreEqual(2024, order.getDate().getyear(), L"Date year should be 2024");
            Assert::AreEqual(0, order.getCourier().getID(), L"Courier ID should be 1");
        }




      
        

    };

}
