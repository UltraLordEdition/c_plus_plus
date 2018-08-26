#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <exception>

using namespace std;

template<typename Key, typename Value, typename K>
Value& GetRefStrict(map<Key, Value>& m, const K& k)
{
    if (m.count(k) == false)
    {
        throw runtime_error("Empty!");
    }
    return m[k];
}

int main() {
    try
    {
        map<int, string> m = { { 0, "value" } };
        string& item = GetRefStrict(m, 0);
        item = "newvalue";
        cout << m[0] << endl; // выведет newvalue
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
}