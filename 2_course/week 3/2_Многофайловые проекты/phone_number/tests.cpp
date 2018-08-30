#include "phone_number.h"
#include "tests.h"

void TestsPhoneNumber()
{
    {
        PhoneNumber p1("+7-952-09598");
        AssertEqual(p1.GetCountryCode(), "7", "Test 1.1");
        AssertEqual(p1.GetCityCode(), "952", "Test 1.2");
        AssertEqual(p1.GetLocalNumber(), "09598", "Test 1.3");
        AssertEqual(p1.GetInternationalNumber(), "+7-952-09598", "Test 1.4");
    }

    {
        PhoneNumber p1("+7-495-111-22-33");
        AssertEqual(p1.GetCountryCode(), "7", "Test 2.1");
        AssertEqual(p1.GetCityCode(), "495", "Test 2.2");
        AssertEqual(p1.GetLocalNumber(), "111-22-33", "Test 2.3");
        AssertEqual(p1.GetInternationalNumber(), "+7-495-111-22-33", "Test 2.4");
    }

    {
        PhoneNumber p1("+7-495-1112233");
        AssertEqual(p1.GetCountryCode(), "7", "Test 3.1");
        AssertEqual(p1.GetCityCode(), "495", "Test 3.2");
        AssertEqual(p1.GetLocalNumber(), "1112233", "Test 3.3");
        AssertEqual(p1.GetInternationalNumber(), "+7-495-1112233", "Test 3.4");
    }

    {
        PhoneNumber p1("+323-22-460002");
        AssertEqual(p1.GetCountryCode(), "323", "Test 4.1");
        AssertEqual(p1.GetCityCode(), "22", "Test 4.2");
        AssertEqual(p1.GetLocalNumber(), "460002", "Test 4.3");
        AssertEqual(p1.GetInternationalNumber(), "+323-22-460002", "Test 4.4");
    }

    {
        PhoneNumber p1("+1-2-coursera-cpp");
        AssertEqual(p1.GetCountryCode(), "1", "Test 5.1");
        AssertEqual(p1.GetCityCode(), "2", "Test 5.2");
        AssertEqual(p1.GetLocalNumber(), "coursera-cpp", "Test 5.3");
        AssertEqual(p1.GetInternationalNumber(), "+1-2-coursera-cpp", "Test 5.4");
    }


    {
        PhoneNumber p1("1-2-333");
        PhoneNumber p2("+7-1233"); 
        PhoneNumber p3("?7-1233");
    }
    
}

void TestsAll()
{
    TestRunner tr;
    tr.RunTest(TestsPhoneNumber, "TestsPhoneNumber");  
}