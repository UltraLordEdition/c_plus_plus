//#include "test_runner.h"
#include <stdexcept>
#include <vector>

using namespace std;

// реализуйте здесь шаблонный класс Deque
template <typename T>
class Deque {
public:

    Deque() {
    }

    Deque(vector<T> front) : front_(front.rbegin(), front.rend()) {
    }

    bool Empty() const {
        return (front_.empty() && back_.empty());
    }

    size_t Size() const {
        return front_.size() + back_.size();
    }

    T& operator[](size_t index) {
        return (front_.size() > index) ? front_[(front_.size() - 1) - index] : back_[index - front_.size()];
    }

    const T& operator[](size_t index) const {
        return (front_.size() > index) ? front_[(front_.size() - 1) - index] : back_[index - front_.size()];
    }

    T& At(size_t index) {
        CheckExcept(index);
        return (front_.size() > index) ? front_[(front_.size() - 1) - index] : back_[index - front_.size()];
    }

    const T& At(size_t index) const {
        CheckExcept(index);
        return (front_.size() > index) ? front_[(front_.size() - 1) - index] : back_[index - front_.size()];
    }

    T& Front() {
        return front_.back();
    }

    const T& Front() const {
        return front_.back();
    }

    T& Back() {
        return back_.empty() ? front_.front() : back_.back();
    }

    const T& Back() const {
        return back_.empty() ? front_.front() : back_.back();
    }

    void PushFront(T indx) {
        front_.push_back(indx);
    }

    void PushBack(T indx) {
        return front_.empty() ? front_.push_back(indx) : back_.push_back(indx);
    }

private:
    void CheckExcept(size_t index) const {
        if (index >= Size()) {
            throw out_of_range("invalid deque<T> subscript");
        }
    }

    vector<T> front_, back_;
};
/*
void TestEmpty() {
    Deque<int> d;
    ASSERT(d.Empty());
}

void TestSize() {
    Deque<int> d({ 1,2,3,4,5 });
    ASSERT_EQUAL(d.Size(), 5u);

    Deque<int> d1;
    ASSERT_EQUAL(d1.Size(), 0u);
}

void TestOperator() {
    Deque<string> d({ "A","B","C","D" });
    d[0] = "E";
    ASSERT_EQUAL(d[0], "E");
    ASSERT_EQUAL(d[1], "B");
    ASSERT_EQUAL(d[2], "C");
    ASSERT_EQUAL(d[3], "D");

    d.PushFront("0");
    d.PushBack("E");
    ASSERT_EQUAL(d[0], "0");
    ASSERT_EQUAL(d[5], "E");
    d.PushFront("1");
    d.PushBack("F");
    ASSERT_EQUAL(d[0], "1");
    ASSERT_EQUAL(d[7], "F");
}

void TestAt() {
    TestOperator();

    Deque<string> d({ "A","B","C","D" });
    //d.At(10) = "E";
}

void TestFrontAndBack() {
    Deque<string> d({ "A","B","C","D" });

    d.PushFront("0");
    d.PushBack("E");
    ASSERT_EQUAL(d[0], d.Front());
    ASSERT_EQUAL(d[d.Size()-1], d.Back());

    d.PushFront("1");
    d.PushFront("2");
    d.PushBack("F");
    d.PushBack("G");
    ASSERT_EQUAL(d[0], d.Front());
    ASSERT_EQUAL(d[d.Size()-1], d.Back());

    Deque<string> d1;
    d1.PushFront("A");
    ASSERT_EQUAL(d1.Front(), "A");
    ASSERT_EQUAL(d1.Back(), "A");

    Deque<string> d2({"A"});
    ASSERT_EQUAL(d2.Front(), "A");
    ASSERT_EQUAL(d2.Back(), "A");
}

void TestPushFrontAndBack() {       // CBADE
    Deque<string> d({ "A" });
    d.PushFront("B");
    d.PushFront("C");
    ASSERT_EQUAL(d.Front(), "C");
    ASSERT_EQUAL(d.Back(), "A");
    d.PushBack("D");
    d.PushBack("E");
    ASSERT_EQUAL(d.Front(), "C");
    ASSERT_EQUAL(d.Back(), "E");
    ASSERT_EQUAL(d[0], "C");
    ASSERT_EQUAL(d[1], "B");
    ASSERT_EQUAL(d[2], "A");
    ASSERT_EQUAL(d[3], "D");
    ASSERT_EQUAL(d[4], "E");
    ASSERT_EQUAL(d.Back(), "E");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestSize);
    RUN_TEST(tr, TestOperator);
    RUN_TEST(tr, TestAt);
    RUN_TEST(tr, TestFrontAndBack);
    RUN_TEST(tr, TestPushFrontAndBack);
    return 0;
}
*/
