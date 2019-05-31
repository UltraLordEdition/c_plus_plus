#include "test_runner.h"
#include <iostream>
#include <numeric>
#include <vector>
#include <future>
using namespace std;

// Шаблон класса Page
template <typename Iterator>
class Page {
public:
    Page() = default;

    Page(Iterator f, Iterator l) : first_page_(f), last_page_(l) {
    }

    Iterator begin() const {
        return first_page_;
    }

    Iterator end() const {
        return last_page_;
    }

    size_t size() const {
        return distance(first_page_, last_page_);
    }

private:
    Iterator first_page_, last_page_;
};

// Реализуйте шаблон класса Paginator
template <typename Iterator>
class Paginator {
public:

    Paginator() = default;

    Paginator(Iterator f, Iterator l, size_t p) : first_(f), last_(l), page_size_(p) {
        for (auto It = first_; It != last_; It = next(It, min(page_size_, static_cast<size_t>(distance(It, last_))))) {
            Page<Iterator> page(It, next(It, min(page_size_, static_cast<size_t>(distance(It, last_)))));
            pages.push_back(page);
        }
    }

    auto begin() {
        return pages.begin();
    }

    auto end() {
        return pages.end();
    }

    const size_t size() const {
        return pages.size();
    }

private:
    const Iterator first_, last_;
    size_t page_size_;
    vector<Page<Iterator>> pages;
};

// Реализуйте этот шаблон функции
template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator{ c.begin(), c.end(), page_size };
}

// сумма матрицы один поток
template<typename Container>
int64_t CalculateSumThread(const Container& matrix) {
  // Реализуйте эту функцию
    int64_t sum = 0;
    for (const auto& row : matrix) {
        for (auto item : row) {
            sum += item;
        }
    }
    return sum;
}

// многопоточный вариант
int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    int64_t sum = 0;
    vector<future<int64_t>> futures;
    for (auto page : Paginate(matrix, 2000u)) {
        futures.push_back(
            async([page, sum] {
            return CalculateSumThread(page);
            })
        );
    }
    for (auto& f : futures) {
        sum += f.get();
    }
    return sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
