#include "test_runner.h"
#include "profile.h"
#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int main() {
    const int SIZE = 5'000'000;

    vector<int> v;
    {   LOG_DURATION("vector");
        for (int i = 0; i < SIZE; ++i) {
            v.push_back(i);
        }
    } // 1346 ms

    deque<int> d;
    {   LOG_DURATION("deque");
        for (int i = 0; i < SIZE; ++i) {
            d.push_back(i);
        }
    } // 1820 ms

    {   LOG_DURATION("sort vector");
        sort(rbegin(v), rend(v));
    } // 6406 ms

    {   LOG_DURATION("sort deque");
        sort(rbegin(d), rend(d));
    } // 16942 ms

    return 0;
}