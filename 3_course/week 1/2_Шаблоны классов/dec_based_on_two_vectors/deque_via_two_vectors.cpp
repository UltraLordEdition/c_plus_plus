//#include "test_runner.h"
#include <utility>
#include <iostream>
#include <vector>

using namespace std;

// реализуйте здесь шаблонный класс Deque
template <typename T>
class Deque {
public:

	Deque() {
		front_;
		back_;
	}

	Deque(vector<T> front) : front_(front) {
	}

	bool Empty() const {
		return (front_.empty() && back_.empty());
	}

	size_t Size() const {
		return front_.size() + back_.size();
	}

	T& operator[](size_t index) {
		if (front_.size() > index) {
			return front_[index];
		}
		else {
			return back_[(Size()-1)-index];
		}
	}

	const T& operator[](size_t index) const {
		if (front_.size() > index) {
			return front_[index];
		}
		else {
			return back_[(Size() - 1) - index];
		}
	}

	T& At(size_t index) {
		if (index >= Size()) {
			throw out_of_range("out of range");
		}
		else if (front_.size() > index) {
			return front_[index];
		}
		else {
			return back_[(Size()-1) - index];
		}
	}

	const T& At(size_t index) const {
		if (index >= Size()) {
			throw out_of_range("out of range");
		}
		else if (front_.size() > index) {
			return front_[index];
		}
		else {
			return back_[(Size() - 1) - index];
		}
	}
	
	T& Front() {
		return front_.front();
	}

	const T& Front() const {
		return front_.front();
	}

	T& Back() {
		if (back_.empty()) {
			return front_.back();
		}
		else {
			return back_.back();
		}
	}

	const T& Back() const {
		if (back_.empty()) {
			return front_.back();
		}
		else {
			return back_.back();
		}
	}

	void PushFront(T indx) {
		front_.insert(front_.begin(), indx);
	}

	void PushBack(T indx) {
		if (front_.empty()) {
			front_.push_back(indx);
		}
		else {
			back_.push_back(indx);
		}
	}

private:
	vector<T> front_, back_;
};

/*
void TestDeque() {
	
	Deque<int> d1;
	ASSERT_EQUAL(d1.Empty(), true);

	Deque<int> d2({ 1,2,3,4,5 });
	ASSERT_EQUAL(d2.Size(), 5u);
	d2[0] = 42;
	ASSERT_EQUAL(d2.Size(), 5u);
	d2.At(0) = 100;
	ASSERT_EQUAL(d2.Front(), 100);
	d2.PushFront(112);
	ASSERT_EQUAL(d2.Front(), 112);
	d2.PushBack(12);
	ASSERT_EQUAL(d2.Back(), 12);
	ASSERT_EQUAL(d2.Size(), 7);
	d2.At(6) = 1000;
	ASSERT_EQUAL(d2.Back(), 1000);
	d2[0] = 1111;
	ASSERT_EQUAL(d2.Front(), 1111);
	d2[6] = 2222;
	ASSERT_EQUAL(d2.Back(), 2222);
	d2[5] = 55;
	d2.At(5) = 555;
	ASSERT_EQUAL(d2.Size(), 7);
	d2.At(0) = 1;
	d2.At(1) = 2;
	d2.At(2) = 3;
	d2.At(3) = 4;
	d2.At(4) = 5;
	d2.At(5) = 6;
	d2.At(6) = 7;
	d2[0] = 11;
	d2[1] = 22;
	d2[2] = 33;
	d2[3] = 44;
	d2[4] = 55;
	d2[5] = 66;
	d2[6] = 77;

	Deque<string> d3;
	d3.PushBack("A");
	cout << d3.Front() << " " << d3.Back();

	Deque<string> d4;
	d4.PushFront("B");
	cout << d4.Front() << " " << d4.Back();

	//d2[7] = 88;
	//d2.At(7) = 555;
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestDeque);
	return 0;
}
*/