#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <utility>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    // Напишите реализацию функции,
    // не копируя сортируемые элементы
    if (distance(range_begin, range_end) > 2u) {
        vector<typename RandomIt::value_type> elements(
            make_move_iterator(range_begin),
            make_move_iterator(range_end)
        );
        vector<typename RandomIt::value_type> temp_elements;
        size_t size = move(elements.size()/3);
        
        MergeSort(
            begin(elements),
            begin(elements) + size
        );
        MergeSort(
            begin(elements) + size,
            begin(elements) + 2 * size
        );
        MergeSort(
            begin(elements) + 2 * size,
            end(elements)
        );
        merge(
            make_move_iterator(begin(elements)),
            make_move_iterator(begin(elements) + size),
            make_move_iterator(begin(elements) + size),
            make_move_iterator(begin(elements) + 2 * size),
            back_inserter(temp_elements)
        );
        merge(
            make_move_iterator(begin(temp_elements)),
            make_move_iterator(end(temp_elements)),
            make_move_iterator(begin(elements) + 2 * size),
            make_move_iterator(end(elements)),
            range_begin
        );
    }
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
