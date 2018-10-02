#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix)
{
    string prefix_str{prefix};
    string next_letter{++prefix};
    auto begin_it = lower_bound(range_begin, range_end, prefix_str);
    auto end_it = lower_bound(begin_it, range_end, next_letter);
    return make_pair(begin_it, end_it);
}

int main() 
{
    const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

    const auto m_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;
    
    const auto p_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " << (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " << (z_result.second - begin(sorted_strings)) << endl;
    
    return 0;
}