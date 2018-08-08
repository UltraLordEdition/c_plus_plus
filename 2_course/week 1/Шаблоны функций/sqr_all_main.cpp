#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

template<typename T> T Sqr(T x);

//Шаблон для умножения пар
template <typename First, typename Second>
pair<First, Second> operator* (const pair<First, Second>& p1, const pair<First, Second>& p2)
{
    First f = p1.first * p2.first;
    Second s = p1.second * p2.second;
    return {f,s};
}

//Шаблон для умножение векторов
template <typename T>
vector<T> operator* (const vector<T>& v1, const vector<T>& v2)
{
    vector<T> sqr;
    for (size_t i = 0; i < v1.size(); ++i)
    {
        sqr.push_back(v1[i] * v2[i]);
    }
    return sqr;
}

//Шаблон для умножения map
template <typename Key, typename Value>
map<Key, Value> operator* (map<Key, Value> m1, map<Key, Value> m2)
{
    map<Key, Value> sqr_m;
    for(auto item = m1.begin(); item != m1.end(); item++)
    {
        sqr_m[item->first] = m1[item->first] * m2[item->first];
    }
    return sqr_m;
}

//шаблон для возведения в квадрат
template <typename T>
T Sqr(T x)
{
    return x*x;
}

int main() {
    
    vector<int> v = { 1,2,3 };
    cout << "vector:";
    for (int x : Sqr(v))
    {
        cout << ' ' << x;
    }
    cout << endl;

    //Создадим пару
    auto p = make_pair(2.5, 3);
    auto res = Sqr(p);
    cout << res.first << endl;
    cout << res.second << endl;

    map<int, pair<int, int>> map_of_pairs = {{ 4, { 2, 2 } }, { 7,{ 4, 3 } }};
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    
    return 0;
}
