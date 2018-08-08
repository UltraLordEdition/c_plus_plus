#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

template <typename First, typename Second>
ostream& operator<< (ostream& out, const pair<First, Second>& p)
{
    out << p.first << ',' << p.second;
    return out;
}

//Объявим шаблонный тип Т
template <typename T>

ostream& operator<< (ostream& out, const vector<T>& vi)
{
    for (const auto& i : vi)
    {
        out << i << ' ';
    }
    return out;
}

template <typename Key, typename Value>
ostream& operator<< (ostream& out, const map<Key, Value>& vi)
{
    for (const auto& i : vi)
    {
        out << i << ' ';
    }
    return out;
}

int main() {
    vector<double> vi = { 1.4,2,3 };
    cout << vi << endl;
    map<int, double> m = { {1,2.5}, {3,4} };
    cout << m << endl;
    return 0;
}