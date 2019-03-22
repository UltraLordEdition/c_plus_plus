#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void TestConstruction() {
  SimpleVector<int> empty;
  ASSERT_EQUAL(empty.Size(), 0u);
  ASSERT_EQUAL(empty.Capacity(), 0u);
  ASSERT(empty.begin() == empty.end());

  SimpleVector<string> five_strings(5);
  ASSERT_EQUAL(five_strings.Size(), 5u);
  ASSERT(five_strings.Size() <= five_strings.Capacity());
  for (auto& item : five_strings) {
    ASSERT(item.empty());
  }
  five_strings[2] = "Hello";
  ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
  SimpleVector<int> v;
  for (int i = 10; i >= 1; --i) {
    v.PushBack(i);
    ASSERT(v.Size() <= v.Capacity());
  }
  sort(begin(v), end(v));

  const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  vector<int> a(begin(v), end(v));
  ASSERT_EQUAL(v.Size(), expected.size());
  ASSERT(equal(begin(v), end(v), begin(expected)));
}

void TestGeneral() {
    {
        SimpleVector<int> v;
        for (size_t i = 0; i < 100; i++) {
            v.PushBack(i);
        }
        for (auto i : v) {
            cerr << i << endl;
        }
        cerr << "begin :" << *v.begin() << endl;
        cerr << "end :" << *(v.end() - 1) << endl;
        cerr << "Size :" << v.Size() << endl;
        cerr << "Capacity :" << v.Capacity() << endl;
    }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConstruction);
  RUN_TEST(tr, TestPushBack);
  RUN_TEST(tr, TestGeneral);
  
  SimpleVector<int> v;
  cout << v.Size() << " " << v.Capacity() << endl;
  v.PushBack(1);              
  cout << v.Size() << " " << v.Capacity() << endl;
  v.PushBack(2);              
  cout << v.Size() << " " << v.Capacity() << endl;
  v.PushBack(3);              
  cout << v.Size() << " " << v.Capacity() << endl;
  v.PushBack(4);              
  cout << v.Size() << " " << v.Capacity() << endl;
  v.PushBack(5);              
  cout << v.Size() << " " << v.Capacity() << endl;
  v.PushBack(6);              
  cout << v.Size() << " " << v.Capacity() << endl;
  v.PushBack(7);              
  cout << v.Size() << " " << v.Capacity() << endl;
  v.PushBack(8);              
  cout << v.Size() << " " << v.Capacity() << endl;
  v.PushBack(9);              
  cout << v.Size() << " " << v.Capacity() << endl;
  v.PushBack(10);             
  cout << v.Size() << " " << v.Capacity() << endl;
  
  for (size_t i = 0; i < 750000000; i++) {
      v.PushBack(i);
  }
  
  return 0;
}
