#include "test_runner.h"
#include "profile.h"
#include <algorithm>
#include <list>
#include <vector>

using namespace std;

class NumbersOnVector {
public:
    void Add(int x) {
        data.push_back(x);
    }

    template<typename Predicate>
    void Remove(Predicate predicate) {
        data.erase(
            remove_if(begin(data), end(data), predicate),
            end(data));
    }

private:
    vector<int> data;
};

class NumbersOnList {
public:
    void Add(int x) {
        data.push_back(x);
    }

    //последний элемент удовлетвор€ющй некоторому условию
    template<typename Predicate>
    auto FindLast(Predicate predicate) {
        return find_if(rbegin(data), rend(data), predicate);
    }

    template<typename Predicate>
    void Remove(Predicate predicate) {
        data.remove_if(predicate);
    }

private:
    list<int> data;
};

// удаление из: vector: 359 ms; list: 2771 ms;
const size_t SIZE1 = 1'000'000;
const size_t REMOVAL_COUNT1 = 10;

// удаление из: vector: 359 ms; list: 2771 ms;
const size_t SIZE = 10000;
const size_t REMOVAL_COUNT = 1000;

int main() {
    /*
    //напишем бенчмарки удалени€
    { LOG_DURATION("vector");
        NumbersOnVector numbers;
        for (int i = 0; i < SIZE; ++i) {
            numbers.Add(i);
        }
        for (int i = 0; i < REMOVAL_COUNT; ++i) {
            numbers.Remove([i](int x) {return x % REMOVAL_COUNT == i; });
        }
    }
    */
    { LOG_DURATION("list");
        NumbersOnList numbers;
        for (int i = 0; i < SIZE; ++i) {
            numbers.Add(i);
        }
        //надем последний элемент который делитс€ на REMOVAL_COUNT
        auto it = numbers.FindLast(
            [](int x) {return x % REMOVAL_COUNT == 0; });
        for (int i = 1; i < REMOVAL_COUNT; ++i) {
            numbers.Remove([i](int x) {return x % REMOVAL_COUNT == i; });
        }
        while (*it != 0) {
            cout << *it << " ";
            ++it;
        }
    }

    return 0;
}