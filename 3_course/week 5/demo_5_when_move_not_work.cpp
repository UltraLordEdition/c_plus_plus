#include "profile.h"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <array>
#include <utility>

using namespace std;

const int SIZE = 10'000;

array<int, SIZE> MakeArray() {
    array<int, SIZE> a;
    a.fill(8);
    return a;
}

string MakeString() {
    return "C++";
}

int main() {
    //����� ������ �� ����� � ���� � ���� ����������� �� ��������
    //������ ����������
    //with variable 1196ms
    {  LOG_DURATION("with variable");
        vector<array<int, SIZE>> arrays;
        for (int i = 0; i < 10'000; ++i) {
            auto heavy_array = MakeArray();
            arrays.push_back(heavy_array);
        }
    }
    //with variable 1145ms
    {  LOG_DURATION("without variable");
        vector<array<int, SIZE>> arrays;
        for (int i = 0; i < 10'000; ++i) {
            arrays.push_back(MakeArray());
        }
    }
    //����� ����������� �� ��������
    //����������� ������������� ����� ���������
    //��������� ���������� const, ����������� �� ��������
    //����� �������� �����������
    vector<string> strings;
    const string s = MakeString();
    cout << s << "\n";
    strings.push_back(move(s));
    cout << s << "\n";

    return 0;
}