#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border)
{
    vector<T> result_vector;
    auto result = find_if(begin(elements), end(elements),
        [&](const T& find)
        {
            return find > border;
        });
    for (auto it = result; it != end(elements); ++it)
    {
        result_vector.push_back(*it);
    }
    return result_vector;
}

int main()
{
    for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5))
    {
        cout << x << " ";
    }
    cout << endl;

    for (int x : FindGreaterElements(set<int>{1, 2, 4, 5, 6, 7}, 3))
    {
        cout << x << " ";
    }
    cout << endl;

    string to_find = "Python";
    cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
    return 0;
}