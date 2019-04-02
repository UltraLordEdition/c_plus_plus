#include "test_runner.h"
#include "profile.h"
#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int main() {
    deque<int> numbers = {1};
    auto it = begin(numbers);
    cout << *it << "\n";

    for (int i = 0; i < 2000; ++i) {
        numbers.push_back(i);
    }
    
    //итераторы в целом мощнее указателей
    //итераторы вектора ожидаемо инвалидируются
    //дек может сохранять указатели валидными,
    //но с итераторами все гораздо сложнее

    //инвалидируется итераторы
    cout << *it <<  " " << *(it + numbers.size()-1) <<  "\n";

    return 0;
}