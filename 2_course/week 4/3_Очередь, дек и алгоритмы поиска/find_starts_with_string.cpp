#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <set>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix)
{
    int size_str = prefix.length();
    string next_letter = prefix;
    ++next_letter[size_str-1];
    
    auto begin_it = lower_bound(range_begin, range_end, prefix);    
    auto end_it = lower_bound(begin_it, range_end, next_letter);
    return make_pair(begin_it, end_it);
}

int main() 
{
    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk" };
            
    const auto mo_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    const auto mt_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " << (mt_result.second - begin(sorted_strings)) << endl;

    const auto na_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " << (na_result.second - begin(sorted_strings)) << endl;
    
    return 0;
}