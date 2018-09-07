#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
    auto result = find_if(begin(numbers), end(numbers),
        [](const int& find)
        {
            return find < 0;
        });
    for (auto it = result; it != begin(numbers);)
    {
        cout << (*--it) << " ";
    }
}

int main()
{
    PrintVectorPart({ 6, 1, 8, -5, 4 });
    PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
    PrintVectorPart({ 6, 1, 8, 5, 4 });

    return 0;
}