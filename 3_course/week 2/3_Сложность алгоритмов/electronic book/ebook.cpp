//#include "test_runner.h"
//#include "profile.h"

#include <algorithm>
#include <iterator>
#include <iomanip>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class ReadingManager {
public:
    ReadingManager() : pages_(1000) {
    }

    void Read(const int& user_id, const int& page_count) {
       for (size_t i = 0; i < pages_.size() && i < page_count; i++) {
           pages_[i].insert(user_id);
       }
    }

    double Cheer(const int& user_id) const {
        float result;
        if (!pages_[0].count(user_id)) {
            return 0;
        }
        if (pages_[0].size() == 1u) {
            return 1.0;
        }
        if (pages_.back().count(user_id)) {
            return (1.0 / (pages_[0].size() - 1.0)) * (pages_[0].size() - (pages_.back().size()));
        }
        for (auto It = begin(pages_); It != pages_.end(); It++) {
            if (!(*It).count(user_id)) {
                result = (1.0 / (pages_[0].size() - 1.0)) * (pages_[0].size() - (*prev(It)).size());
                return result;
            }
        }        
    }

private:
    vector<set<int>> pages_;
};
/*
void TestRead() {
    {
        ReadingManager manager;
        vector<set<int>> p = { {1}, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 } };
        manager.Read(1, 10);
        ASSERT_EQUAL(manager.pages_, p);
    }
    {
        ReadingManager manager;
        vector<set<int>> p = { {1,2,3}, { 1,2,3 }, { 1,2,3 }, { 1,2,3 }, { 1,2,3 }, { 1,3 }, { 1,3 }, { 1 }, { 1 }, { 1 } };
        manager.Read(1, 10);
        manager.Read(2, 5);
        manager.Read(3, 7);
        ASSERT_EQUAL(manager.pages_, p);
    }
    {
        ReadingManager manager;
        vector<set<int>> p = { {1,2,3}, { 1,2,3 }, { 1,2,3 }, { 1,2,3 }, { 1,2,3 }, { 1,3 }, { 1,3 }, { 1,3 }, { 1,3 }, { 1,3 } };
        manager.Read(1, 10);
        manager.Read(2, 5);
        manager.Read(3, 7);
        manager.Read(3, 10);
        ASSERT_EQUAL(manager.pages_, p);
    }
}

void TestCheer() {
    {
        ReadingManager manager;
        vector<set<int>> p = { {1}, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 } };
        manager.Read(1, 11);
        ASSERT_EQUAL(manager.Cheer(1), 1);
    }
    {
        ReadingManager manager;
        vector<set<int>> p = { {1,2,3,4,5,6}, { 1,2,3,4,5,6 }, { 1,2,3,4,5,6 }, { 1,2,3,4,6 }, { 1,2,3,4,6 }, { 1,3,4,6 }, { 1,3 }, { 1,3 }, { 1,3 }, { 1,3 }, { 3 } };
        manager.Read(1, 10);
        manager.Read(2, 5);
        manager.Read(3, 11);
        manager.Read(4, 6);
        manager.Read(5, 3);
        manager.Read(6, 7);
        ASSERT_EQUAL(manager.Cheer(1), 0.8);
        ASSERT_EQUAL(manager.Cheer(2), 0.2);
        ASSERT_EQUAL(manager.Cheer(3), 1.0);
        ASSERT_EQUAL(manager.Cheer(4), 0.4);
        ASSERT_EQUAL(manager.Cheer(5), 0);
        ASSERT_EQUAL(manager.Cheer(6), 0.6);
    }
    {
        ReadingManager manager;
        vector<set<int>> p = { {1,2,3}, { 1,2,3 }, { 1,2,3 }, { 1,2,3 }, { 1,2,3 }, { 1,3 }, { 1,3 }, { 1,3 }, { 1,3 }, { 1,3 }, { 1,3 } };
        ASSERT_EQUAL(manager.Cheer(5), 0);
        manager.Read(1, 11);
        ASSERT_EQUAL(manager.Cheer(1), 1);
        manager.Read(2, 5);
        manager.Read(3, 8);
        ASSERT_EQUAL(manager.Cheer(2), 0);
        ASSERT_EQUAL(manager.Cheer(3), 0.5);
        manager.Read(3, 11);
        ASSERT_EQUAL(manager.Cheer(3), 0.5);
    }
}

void TestAll() {
    TestRunner tr;
    RUN_TEST(tr, TestRead);
    RUN_TEST(tr, TestCheer);
}
*/
int main() {
    //TestAll();
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << endl;
        }
    }

    return 0;
}