#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

void PrintRange(vector<int>::iterator range_begin, vector<int>::iterator range_end)
{
    for (auto it = range_begin; it != range_end; ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}

int main()
{
    int a;
    cin >> a;
    vector<int> v(a);
    iota(rbegin(v), rend(v), 1);
    do {
        PrintRange(begin(v), end(v));
    } while (prev_permutation(begin(v), end(v)));
        
    return 0;
}
