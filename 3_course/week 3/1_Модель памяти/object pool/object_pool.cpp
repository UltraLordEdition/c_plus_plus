#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    ObjectPool() {
    }

    T* Allocate() {
        if (_liberty.size() > 0) {
            T* n = _liberty.front();
            _select.insert(n);
            _liberty.pop();
            return n;
        }
        else {
            T* n = new T;
            _select.insert(n);
            return n;
        }
    }
    T* TryAllocate() {
        if (_liberty.empty() || _liberty.size() == 0) {
            return nullptr;
        }
        else {
            T* n = _liberty.front();
            _select.insert(n);
            _liberty.pop();
            return n;
        }
    }

    void Deallocate(T* object) {
        if (_select.count(object) == 0) {
            throw invalid_argument("");
        }
        _liberty.push(*_select.find(object));
        _select.erase(object);
    }

    ~ObjectPool() {
        for (auto it : _select) {
            delete it;
        }
        while (!_liberty.empty()) {
            delete _liberty.front();
            _liberty.pop();
        }
    }

private:
    // Добавьте сюда поля
    queue<T*> _liberty;
    set<T*> _select;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);

    return 0;
}
