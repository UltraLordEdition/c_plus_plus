#include "test_runner.h"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Table {
public:
    Table(size_t rows, size_t colums) {
        Resize(rows, colums);
    }

    vector<T>& operator[] (size_t idx) {
        return date[idx];
    }

    const vector<T>& operator[] (size_t idx) const {
        return date[idx];
    }

    void Resize(size_t rows, size_t colums) {
        date.resize(rows);
        for (auto& item : date) {
            item.resize(colums);
        }
    }

    pair<size_t, size_t> Size() const {
        return { date.size(), (date.empty() ? 0 : date[0].size()) };
    }

private:
    vector<vector<T>> date;
};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
