#include "test_runner.h"
#include <iostream>
#include <vector>

using namespace std;

// Реализуйте здесь шаблонный класс Deque
template <typename T>
class Deque {
public:

    Deque(vector<T> front) : front_(front) {
    }

    bool Empty() const {
        return (front_.empty() && back_.empty()) ? true : false;
    }

    size_t Size() const {
        return front_.size() + back_.size();
    }

    T& operator[](size_t index) {

    }
    
    const T& operator[](size_t index) const {

    }

    void At(size_t index) {

    }

    void At(size_t index) const {

    }

    void Front() {

    }

    void Front() const {

    }

    void Back() {

    }

    void Back() const {

    }

    void PushFront() {
    }
    
    void PushBack() {

    }

private:
    vector<T> front_, back_;
};


void TestDeque() {
    Deque<int> d({ 1,2,3,4,5 });
    //ASSERT_EQUAL(t.Size().first, 1u);
    //ASSERT_EQUAL(t.Size().second, 1u);
    //t[0][0] = 42;
    /*ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);*/
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestDeque);
    return 0;
}
