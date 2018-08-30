#include "stdafx.h"
#include "tests.h"
#include "sum_reverse_sort.h"

//Implementation

void TestSum()
{
    AssertEqual(Sum(5, 5), 10, "expected result 10");
    AssertEqual(Sum(-5, -5), -10, "expected result 0");
    AssertEqual(Sum(-5, 2), -3, "expected result -3");
    AssertEqual(Sum(5, -2), 3, "expected result 3");
}

void TestReverse()
{
    AssertEqual(Reverse("0123456789"), "9876543210", "Revers not work!");
}

void TestSort()
{
    vector<int>         v1 = { 1,5,6,8,9,0,3,7,2,4 };
    const vector<int>   v2 = { 0,1,2,3,4,5,6,7,8,9 };
    Sort(v1);
    AssertEqual(v1, v2, "Vectors not equal!");
}

void TestAll()
{
    TestRunner tr;
    tr.RunTest(TestSum, "TestSum");
    tr.RunTest(TestReverse, "TestReverse");
    tr.RunTest(TestSort, "TestSort");
    //дальше объект tr класса TestRunner будет разрушаться
    //функция закончилась и не какие тесты больше не будут вызываться
    //поэтому анализ переменной fail_count поместим в деструктор класса TestRunner
}