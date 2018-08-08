#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//Ўаблон дл€ умножени€ пар
template <typename First, typename Second>
pair<First, Second> operator* (const pair<First, Second>& p1, const pair<First, Second>& p2)
{
    First f = p1.first*p2.first;
    Second s = p1.second*p2.second;
    return make_pair(f, s);
}

//ќбъ€вл€ем элемент типа T
//template шаблоные параметры типы
template <typename T>
T Sqr(T x)
{
    return x * x;
}

int main() {
    //—оздадим пару
    auto p = make_pair(2.5, 3);
    auto res = Sqr(p);
    cout << res.first << endl;
    cout << res.second << endl;
    return 0;
}