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

uint64_t getMass(const uint64_t& W, const uint64_t H, const uint64_t D, const uint64_t R)
{
    uint64_t mass = W*H*D*R;
    return mass;
}

int main()
{
    uint32_t N, R, W, H, D;
    uint64_t sumMass = 0;
    cin >> N >> R;
    for (int i = 0; i < N; ++i)
    {
        cin >> W >> H >> D;
        sumMass += getMass(W, H, D, R);
    }
    cout << sumMass << endl;
    return 0;
}