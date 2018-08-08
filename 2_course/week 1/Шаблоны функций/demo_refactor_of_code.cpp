#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

//���������� � ��������: �� ��� ����� ���� ����� ������������� � ������� range based-for;
//� �� �������� ������ ���� ����� �������� � �����
template <typename Collection>
//�������� ��������� � ����������� � ��������� ������� Join
string Join(const Collection& c, char d)
{
    stringstream ss;
    //���� ������� ������� ������ ������� ��� ���
    bool first = true;
    for (const auto& i : c)
    {
        if (!first)
        {
            ss << d;
        }
        first = false;
        ss << i;        //������� �������� � �����
    }
    return ss.str();
}

template <typename First, typename Second>
ostream& operator<< (ostream& out, const pair<First, Second>& p)
{
   return  out << '(' << p.first << ',' << p.second << ')';
}

//������� ��������� ��� �
template <typename T>
ostream& operator<< (ostream& out, const vector<T>& vi)
{
    return out << '[' << Join(vi, ',') << ']';
}

template <typename Key, typename Value>
ostream& operator<< (ostream& out, const map<Key, Value>& m)
{
    return out << '{' << Join(m,',') << '}';
}

int main() {
    vector<double> vi = { 1.4,2,3 };
    cout << vi << endl;

    vector<vector<int>> v = { {1,2},{3,4} };
    cout << v << endl;

    map<int, double> m = { {1,2.5}, {3,4} };
    cout << m << endl;
    return 0;
}