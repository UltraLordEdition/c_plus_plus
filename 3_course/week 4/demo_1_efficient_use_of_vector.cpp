#include "test_runner.h"
#include "profile.h"
#include <iostream>
#include <vector>

using namespace std;

void LogVectorParams(const vector<int>& v) {
    cout << "Length = " << v.size() << ", " <<
        "capacity = " << v.capacity() << "\n";
    
    //data() ���������� ����������� ��������
    const int* data = v.data();
    for (size_t i = 0; i < v.capacity(); ++i) {
        cout << *(data + i) << " ";
    }
    cout << endl;
}

int main() {
    {
        vector<int> v = { 1, 2, 3 };
        LogVectorParams(v);
        //������� capacity
        v.push_back(4);
        v.push_back(5);
        LogVectorParams(v);
        //��������� ����� (�������� �� �������)
        v.shrink_to_fit();
        LogVectorParams(v);
    }
    //������ � ������ ����� ������� ���� ������� �� 10'000'000
    int size;
    cin >> size;
    { LOG_DURATION("push_back");
      vector<int> v;
      for (int i = 0; i < size; ++i) {
        v.push_back(i);
      }
    }// 7411 ms
    
    //������� �������
    { LOG_DURATION("push_back");
    vector<int> v;
    v.reserve(size);
    for (int i = 0; i < size; ++i) {
        v.push_back(i);
    }
    }// 7411 ms

    return 0;
}