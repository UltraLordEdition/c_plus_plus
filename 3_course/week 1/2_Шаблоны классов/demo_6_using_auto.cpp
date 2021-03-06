#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <deque>
using namespace std;

template <typename Iterator>
class IteratorRange {
private:
	Iterator first, last;

public:
	IteratorRange(Iterator f, Iterator l) : first(f), last(l)
	{
	}

	Iterator begin() const {
		return first;
	}
	Iterator end() const {
		return last;
	}
};

template <typename Container>
//Напишем тип auto, говорим чтобы компилятор взял тип из return
auto Head(Container& v, size_t top) {
	return IteratorRange{								//напишем IteratorRange тем самым говорим что возвращать нужно тип Container::iterator
		v.begin(), next(v.begin(), min(top, v.size()))
	};
}

//IteratorRange - шаблон типа. Инстанцируем шаьлон типом T
template <typename T>
size_t RangeSize(IteratorRange<T> r) {		//конкретный тип
	return r.end() - r.begin();
}

//Напишем пораждающуюю функцию
template<typename Iterator>
IteratorRange<Iterator> MakeRange(Iterator begin, Iterator end) {
	return IteratorRange <Iterator>{begin, end};
}

int main() {
	vector<int> v = { 1,2,3,4,5 };
	for (int& x : Head(v, 3)) {
		++x;
	}
	for (int x : v) {
		cout << x << ' ';
	}
	cout << endl;

	set<int> nums = { 5, 7, 12, 8, 10, 5, 6, 1 };
	for (int x : Head(nums, 4)) {
		cout << x << ' ';
	}
	cout << endl;

	const deque<int> nums2 = { 5, 7, 12, 8, 10, 5, 6, 1 };
	for (int x : Head(nums2, 4)) {
		cout << x << ' ';
	}
	cout << endl;
}