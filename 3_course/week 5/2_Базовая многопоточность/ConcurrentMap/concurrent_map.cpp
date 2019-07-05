#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include <future>
#include <mutex>
#include <map>

using namespace std;

template <typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access {
        V& ref_to_value;
        lock_guard<mutex> guard;
    };

    explicit ConcurrentMap(size_t bucket_count) : thread_count_(bucket_count),  base_(bucket_count) {
    }

    Access operator[](const K& key) {
        return { base_[getCounter() - 1u][key], lock_guard(m) };
    }
   
    map<K, V> BuildOrdinaryMap() {
        LOG_DURATION("BuildOrdinaryMap()");
        for (auto& it : base_) {
            for (const auto&[key, value] : it) {
                if (submap_.count(key)) {
                    submap_[key] += value;
                }  
                submap_.insert({ key,value });
            }
        }
        return move(submap_);
    }

private:
    size_t& getCounter() {
        lock_guard<mutex> g(m);
        if (counter_ < thread_count_) {
            counter_++;
        }
        else {
            counter_ = 1;
        }
        return counter_;
    }
    
    const size_t thread_count_;
    size_t counter_;
    map<K, V> submap_;
    vector<map<K, V>> base_;
    mutex m;
};

void RunConcurrentUpdates(ConcurrentMap<int, int>& cm, size_t thread_count, int key_count) {
    LOG_DURATION("kernel");
    auto kernel = [&cm, key_count](int seed) {
        vector<int> updates(key_count);
        iota(begin(updates), end(updates), -key_count / 2);
        shuffle(begin(updates), end(updates), default_random_engine(seed));

        for (int i = 0; i < 2; ++i) {
            for (auto key : updates) {
                cm[key].ref_to_value++;
            }
        }
    };
    
    {LOG_DURATION("vector_future");
    vector<future<void>> futures;
    for (size_t i = 0; i < thread_count; ++i) {
        futures.push_back(async(kernel, i));
    }
    }
}

void TestConcurrentUpdate() {
    const size_t thread_count = 3;
    const size_t key_count = 50000;

    ConcurrentMap<int, int> cm(thread_count);
    RunConcurrentUpdates(cm, thread_count, key_count);

    const auto result = cm.BuildOrdinaryMap();
    ASSERT_EQUAL(result.size(), key_count);
    for (auto&[k, v] : result) {
        AssertEqual(v, 6, "Key = " + to_string(k));
    }
}

void TestReadAndWrite() {
    ConcurrentMap<size_t, string> cm(5);

    auto updater = [&cm] {
        for (size_t i = 0; i < 50000; ++i) {
            cm[i].ref_to_value += 'a';
        }
    };
    auto reader = [&cm] {
        vector<string> result(50000);
        for (size_t i = 0; i < result.size(); ++i) {
            result[i] = cm[i].ref_to_value;
        }
        return result;
    };

    auto u1 = async(updater);
    auto r1 = async(reader);
    auto u2 = async(updater);
    auto r2 = async(reader);

    u1.get();
    u2.get();

    for (auto f : { &r1, &r2 }) {
        auto result = f->get();
        ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
            return s.empty() || s == "a" || s == "aa";
        }));
    }
}

void TestSpeedup() {
    {
        ConcurrentMap<int, int> single_lock(1);

        LOG_DURATION("Single lock");
        RunConcurrentUpdates(single_lock, 4, 50000);
    }
    {
        ConcurrentMap<int, int> many_locks(100);

        LOG_DURATION("100 locks");
        RunConcurrentUpdates(many_locks, 4, 50000);

        /*
        const auto result = many_locks.BuildOrdinaryMap();
        ASSERT_EQUAL(result.size(), 50000);
        for (auto&[k, v] : result) {
            AssertEqual(v, 8, "Key = " + to_string(k));
        }*/
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestConcurrentUpdate);
    RUN_TEST(tr, TestReadAndWrite);
    RUN_TEST(tr, TestSpeedup);
}
