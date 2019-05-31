#include "profile.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <future>

using namespace std;

// ������ ������ Page
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

// ���������� ������ ������ Paginator
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

// ���������� ���� ������ �������
template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator{ c.begin(), c.end(), page_size };
}

// ������������ �������
template<typename ContainerOfVectors>
void GenerateSingleThread(ContainerOfVectors& result, size_t first_row, size_t column_size) {
    for (auto& row : result) {
        row.reserve(column_size);
        for (size_t column = 0; column < column_size; ++column) {
            row.push_back(first_row^column);
        }
        ++first_row;
    }
}

vector<vector<int>> GenerateSingleThread(size_t size) {
    vector<vector<int>> result(size);
    GenerateSingleThread(result, 0, size);
    return result;
}

template<typename ContainerOfVectors>
int64_t SumSingleThread(const ContainerOfVectors& matrix) {
    int64_t sum = 0;
    for (const auto& row : matrix) {
        for (auto item : row) {
            sum += item;
        }
    }
    return sum;
}

// ������������� �������
// size - ������ �������; page_size - ������ ��������;
vector<vector<int>> GenerateMultiThread(size_t size, size_t page_size) {
    vector<vector<int>> result(size);
    vector<future<void>> futures;
    //���������� ������
    size_t first_row = 0;
    for (auto page : Paginate(result, page_size)) {
    // !!! �����
    // �������� ������� ���� future, �� ����������� ����� �� �����������
    // ���� �� ���������, �� async ������� ��������� ������, �� �� ���� �� ����������,
    // � ���� ����� ���������� ����������. �� ����� ����������� ������ �� ����������
        futures.push_back(
            async([page, first_row, size] {
            GenerateSingleThread(page, first_row, size);
            })
        );
        first_row += page_size;
    }
    /* �������� ������� ��������� ���������� �������
    // ����� ����� ��� � ���� � �����
    for (auto f : futures) {
        f.get();
    }*/

    return result;
    // ����� ����������� ���������� �������, ����������� ������ futures
    // ���������� ���������� ������� futures -> ��������������� ����������
    // ����������� future<void>. ��� ����������� �������� .get() � ����������
    // ��������� ����������� ��������. ��� ��� ��� �������� ����� ���� ��� �� �� �������� future
    // ��� ���� ����� ����� �������. �� ���������� ����������� ���������� ����� �������
}
// !!! �����
// future<T>, ��������� � ������� async, �������� get() � ����� �����������
// ���� ��������� ������ async �� ��������� � ����������,
// �� ��������� ����� ����������� ���������������

int main() {
    LOG_DURATION("Total");
    const size_t matrix_size = 7000;

    //sum = 195928050144

    vector<vector<int>> matrix;
    {
        LOG_DURATION("Single thread generation");
        matrix = GenerateSingleThread(matrix_size);
    }
    {
        LOG_DURATION("Multi thread generation");
        matrix = GenerateMultiThread(matrix_size, 2000);
    }
    {
        LOG_DURATION("Single thread sum");
        cout << SumSingleThread(matrix) << endl;
    }

    return 0;
} 