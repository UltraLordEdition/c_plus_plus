#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <fstream>
#include <limits>
#include <tuple>
#include <utility>

using namespace std;
/*
int main() {
    //pair<int, string> p(7, "C++");               //��������� ���������� p ���� ����
    //auto p = make_pair(7, "C++");        //��������� ���������� p ���� ����
    pair p(7, "C++");               //��������� ���������� p ���� ����
    cout << p.first << " " << p.second << endl;

    return 0;
}
*/

int main()
{
    map<int, string> digits = { {1,"one"} };
    /*
    for (const pair<int,string>& item : digits)
    {
        cout << item.first << " " << item.second << endl;
    }
    */
    //�������� �++ 17
    for (const auto&[key, value] : digits)
    {
        cout << key << " " << value << endl;
    }
}