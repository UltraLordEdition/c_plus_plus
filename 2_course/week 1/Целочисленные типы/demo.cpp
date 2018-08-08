#include "stdafx.h"
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
//Introduction in integer types
/*
int main() {
    cout << sizeof(unsigned int) << endl;
    cout << numeric_limits<unsigned int>::min() << " " << numeric_limits<unsigned int>::max() << endl;
    return 0;
}
*/
/*
void PrintAvg()
{
    vector<int> t = { -8,-7,3 };
    int sum = 0;
    for (int x : t)
    {
        sum += x;
    }
    int avg = sum / static_cast<int>(t.size());
    cout << avg << endl;
}*/

int main()
{
    //PrintAvg();
    
    
    vector<int> v = {1,4,5};
    
    for (size_t i = 0; i+1<v.size(); ++i)
    {
        cout << v[i] << endl;
    }
    
    for (size_t k = v.size(); k > 0; --k)
    {
        size_t i = k - 1;
        cout << v[i] << endl;
    }

    return 0;
}