#include "stdafx.h"
#include "test_runner.h"

//template AssertEqual in all unit-tests
void Assert(bool b, const string& hint)
{
    AssertEqual(b, true, hint);
}

//здесь будем анализировать переменную fail_count
TestRunner::~TestRunner()
{
    if (fail_count > 0)
    {
        cerr << fail_count << " tests failed. Terminate";
        //завершим выполнение программы с переданным в нее кодом возврата
        //это наследие С
        exit(1);
    }
}