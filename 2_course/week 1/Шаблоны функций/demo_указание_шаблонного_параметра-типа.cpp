#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;
/*
template <typename T>
T Max(T a, T b)
{
    if (b < a)
    {
        return a;
    }
    return b;
}


int main() {
    //Приведем аргументы функции к типу <int>
    cout << Max<int>(2, 3.5) << endl;
    return 0;
}
*/

int main() {
    //Приведем аргументы функции к типу <int>
    cout << max<double>(2, 3.5) << endl;
    return 0;
}
