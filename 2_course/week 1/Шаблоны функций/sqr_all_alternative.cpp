#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <exception>

using namespace std;

// Объявим функции без тела,
// чтобы их можно было использовать в произвольном порядке

// Для простых типов
template<typename T>
T Sqr(T x);

// Для вектора
template<typename T>
vector<T> Sqr(const vector<T>& v);

// Для пары
template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p);

// Для словаря
template<typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m);

//Шаблон для умножения map
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

//Шаблон для умножения пар
template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p)
{
   return { Sqr(p.first), Sqr(p.second) };
}

//Шаблон для умножение векторов
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

//шаблон для возведения в квадрат
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
    
    //Создадим пару
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
