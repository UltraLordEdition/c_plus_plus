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

using namespace std;

int main() {
    //tuple<int, string, bool> t(7, "C++", true);   //��������� ���������� t ���� ������
    tuple t(7, "C++", true);                        //�������� C++ 17   
    //auto t = make_tuple(7, "C++", true);          //������� ������ 
    cout << get<1>(t) << endl;                      //������� � ������� "C++"

    return 0;
}