#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//������ ��� ��������� ���
template <typename First, typename Second>
pair<First, Second> operator* (const pair<First, Second>& p1, const pair<First, Second>& p2)
{
    First f = p1.first*p2.first;
    Second s = p1.second*p2.second;
    return make_pair(f, s);
}

//��������� ������� ���� T
//template �������� ��������� ����
template <typename T>
T Sqr(T x)
{
    return x * x;
}

int main() {
    //�������� ����
    auto p = make_pair(2.5, 3);
    auto res = Sqr(p);
    cout << res.first << endl;
    cout << res.second << endl;
    return 0;
}