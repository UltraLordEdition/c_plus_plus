#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (range_end - range_begin < 2)
    {
        return;
    }
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    size_t size = elements.size()/2;
    MergeSort(begin(elements), begin(elements)+size);
    MergeSort(begin(elements)+size, end(elements));
    merge(begin(elements), begin(elements)+size, begin(elements)+size, end(elements), range_begin);
}

int main()
{
    vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    
    return 0;
}