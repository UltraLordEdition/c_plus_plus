#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <fstream>
#include <limits>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> temperatures(n);
    int64_t sum = 0;
    for (int& temperature : temperatures)
    {
        cin >> temperature;
        sum += temperature;
    }

    int average = sum/n;
    vector<int> result_indices;
    for (int i = 0; i < n; ++i)
    {
        if (temperatures[i] > average)
        {
            result_indices.push_back(i);
        }
    }
    cout << result_indices.size() << endl;
    for (const int& item : result_indices)
    {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}