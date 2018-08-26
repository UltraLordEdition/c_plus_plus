#include "stdafx.h"
#include <iostream>
#include <cassert>

using namespace std;

int Sum(int x, int y)
{
    if (x < 0)
    {
        x -= 1;
        return x + y;
    }
}

void TestSum()
{
    assert(Sum(2, 3) == 5);
    assert(Sum(-2, -3) == -5);
    assert(Sum(-2, 0) == -2);
    assert(Sum(-2, 2) == 0);
    cout << "TestSum OK" << endl;
}

int main() {
    TestSum();
    return 0;
}