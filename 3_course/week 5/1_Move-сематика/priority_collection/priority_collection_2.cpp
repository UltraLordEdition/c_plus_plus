#include "test_runner.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = size_t;    /* тип, используемый для идентификаторов */;

  PriorityCollection() {
    id_.reserve(1'000'000);
  }

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
      id_.push_back({move(object)});
      base_.insert({0u, id_.size()-1u});
      return id_.size()-1u;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
      for (; range_begin != range_end; range_begin++) {
          *(ids_begin++) = Add(move(*range_begin));
      }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
      if (id_.size() >= id) {
          return id_[id].status_;
      }
      return false;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
      return id_[id].object_;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
      base_.erase({id_[id].priority_, id});
      id_[id].priority_++;
      base_.insert({id_[id].priority_, id});
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
      return {id_[crbegin(base_)->second].object_, crbegin(base_)->first};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
      auto last = prev(base_.end());
      id_[last->second].status_ = false;
      pair<T, int> tmp = {move(id_[last->second].object_), last->first};
      base_.erase(last);
      return move(tmp);
  }

private:
  // Приватные поля и методы
  struct Object {
      T object_;
      bool status_ = true;
      int priority_ = 0u;
  };

  set<pair<int,Id>> base_;
  vector<Object> id_;
};

class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");
  
  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto it = strings.GetMax();
    ASSERT_EQUAL(it.first, "red");
    ASSERT_EQUAL(it.second, 2);

    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto it = strings.GetMax();
    ASSERT_EQUAL(it.first, "yellow");
    ASSERT_EQUAL(it.second, 2);

    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto it = strings.GetMax();
    ASSERT_EQUAL(it.first, "white");
    ASSERT_EQUAL(it.second, 0);

    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
  strings.Add("white");
  ASSERT_EQUAL(strings.IsValid(0), false);
  ASSERT_EQUAL(strings.IsValid(1), false);
  ASSERT_EQUAL(strings.IsValid(2), false);
  ASSERT_EQUAL(strings.IsValid(3), true);
  ASSERT_EQUAL(strings.IsValid(100), false);
}

void TestNoCopyGet() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  ASSERT_EQUAL(strings.Get(white_id), "white");
  ASSERT_EQUAL(strings.Get(yellow_id), "yellow");
  ASSERT_EQUAL(strings.Get(red_id), "red");

  ASSERT_EQUAL(strings.IsValid(0), true);
  ASSERT_EQUAL(strings.IsValid(1), true);
  ASSERT_EQUAL(strings.IsValid(2), true);
  ASSERT_EQUAL(strings.IsValid(100), false);
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  RUN_TEST(tr, TestNoCopyGet);

  return 0;
}
