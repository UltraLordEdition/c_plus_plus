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
    vector<typename RandomIt::value_type> temp_elements;

    size_t size = elements.size()/3;
    MergeSort(begin(elements), begin(elements)+size);
    MergeSort(begin(elements)+size, begin(elements)+2*size);
    MergeSort(begin(elements)+2*size, end(elements));
    merge(begin(elements), begin(elements)+size, begin(elements)+size, begin(elements)+2*size, back_inserter(temp_elements));
    merge(begin(temp_elements), end(temp_elements), begin(elements) + 2*size, end(elements), range_begin);
}

int main()
{
    vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
    MergeSort(begin(v), end(v));
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}