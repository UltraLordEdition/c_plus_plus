#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

pair<ifstream, ofstream> MakeStreams(const string& prefix) {
    ifstream input;
    ofstream output;
    return { ifstream(prefix + ".in"),ofstream(prefix + ".out") };
}

ifstream MakeInputStream(const string& prefix) {
    auto streams = MakeStreams(prefix);
    //return streams).first - не верно
    return move(streams).first;
    return MakeStreams(prefix).first; // так еще лучше
}

int main() {
    return 0;
}
