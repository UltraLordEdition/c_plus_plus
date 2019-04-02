#include "test_runner.h"
#include "profile.h"
#include <iostream>
#include <vector>

using namespace std;

void LogVectorParams(const vector<int>& v) {
    cout << "Length = " << v.size() << ", " <<
        "capacity = " << v.capacity() << "\n";
    
    //data() возвращает константный уазатель
    const int* data = v.data();
    for (size_t i = 0; i < v.capacity(); ++i) {
        cout << *(data + i) << " ";
    }
    cout << endl;
}

int main() {
    vector<int> v = { 1,2,3 };
    int& first = v[0];
    cout << first << "\n";
    v.push_back(4);
    //ссылка first инвалидируется
    cout << first << "\n";

    return 0;
}