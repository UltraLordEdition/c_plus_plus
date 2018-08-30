#include "stdafx.h"
#include "test_runner.h"

//template AssertEqual in all unit-tests
void Assert(bool b, const string& hint)
{
    AssertEqual(b, true, hint);
}

//����� ����� ������������� ���������� fail_count
TestRunner::~TestRunner()
{
    if (fail_count > 0)
    {
        cerr << fail_count << " tests failed. Terminate";
        //�������� ���������� ��������� � ���������� � ��� ����� ��������
        //��� �������� �
        exit(1);
    }
}