#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <exception>

using namespace std;

// ������� ������� ��� ����,
// ����� �� ����� ���� ������������ � ������������ �������

// ��� ������� �����
template<typename T>
T Sqr(T x);

// ��� �������
template<typename T>
vector<T> Sqr(const vector<T>& v);

// ��� ����
template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p);

// ��� �������
template<typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m);

//������ ��� ��������� map
template<typename Key, typename Value> 
map<Key, Value> Sqr(const map<Key, Value>& m)
{
    map<Key, Value> sqr;
    for (const auto& i : m)
    {
        sqr[i.first] = Sqr(i.second);
    }
    return sqr;
}

//������ ��� ��������� ���
template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p)
{
   return { Sqr(p.first), Sqr(p.second) };
}

//������ ��� ��������� ��������
template <typename T>
vector<T> Sqr(const vector<T>& v)
{
    vector<T> sqr;
    for (const auto& i : v)
    {
        sqr.push_back(Sqr(i));
    }
    return sqr;
}

//������ ��� ���������� � �������
template <typename T>
T Sqr(T x)
{
    return x * x;
}

int main() {
    vector<int> v = { 1,2,3 };
    cout << "vector:";
    for (int x : Sqr(v))
    {
        cout << ' ' << x;
    }
    cout << endl;
    
    //�������� ����
    auto p = make_pair(2.5, 3);
    auto res = Sqr(p);
    cout << res.first << endl;
    cout << res.second << endl;
    
    map<int, pair<int, int>> map_of_pairs = { { 4,{ 2, 2 } },{ 7,{ 4, 3 } } };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    
    return 0;
}
