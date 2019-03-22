#include "test_runner.h"

#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;
  };

  //����� ������� ������ ��� ������ �������
  LinkedList() {
  }

  ~LinkedList() {
      while (head != nullptr) {
        PopFront();
      }
  }

  void PushFront(const T& value) {
      Node* new_head = new Node;

      new_head->value = value;
      new_head->next = head;
      head = new_head;
  }

  void InsertAfter(Node* node, const T& value) {
      if (node == nullptr) {
          PushFront(value);
      }
      else {
          Node* add_node = new Node;
          add_node->value = value;
          add_node->next = node->next;
          node->next = add_node;
      }
  }

  void RemoveAfter(Node* node) {
      if (node == nullptr) {
          PopFront();
      }
      else if (node->next != nullptr) {
          Node* del;
          del = node->next;
          node->next = node->next->next;
          delete del;
      }
  }

  void PopFront() {
      if (head != nullptr) {
          Node* del;
          del = head;
          head = head->next;
          delete del;
      }
  }

  Node* GetHead() { return head;}

  const Node* GetHead() const { return head;}

private:
  Node* head = nullptr;
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
  vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

void TestPushFront() {
  LinkedList<int> list;

  list.PushFront(1);
  ASSERT_EQUAL(list.GetHead()->value, 1);
  list.PushFront(2);
  ASSERT_EQUAL(list.GetHead()->value, 2);
  list.PushFront(3);
  ASSERT_EQUAL(list.GetHead()->value, 3);

  const vector<int> expected = {3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
  {
    LinkedList<string> list;

    list.PushFront("a");
    auto head = list.GetHead();
    ASSERT(head);
    ASSERT_EQUAL(head->value, "a");

    list.InsertAfter(head, "b");
    const vector<string> expected1 = { "a", "b" };
    ASSERT_EQUAL(ToVector(list), expected1);

    list.InsertAfter(head, "c");
    const vector<string> expected2 = { "a", "c", "b" };
    ASSERT_EQUAL(ToVector(list), expected2);
  }
  {
    LinkedList<string> list;
    auto head = list.GetHead();
    list.InsertAfter(head, "a");
    const vector<string> expected = { "a"};
    ASSERT_EQUAL(ToVector(list), expected);
  }
}

void TestRemoveAfter() {
  LinkedList<int> list;
  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }

  const vector<int> expected = {5, 4, 3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);

  auto next_to_head = list.GetHead()->next;
  list.RemoveAfter(next_to_head); // ������� 3
  list.RemoveAfter(next_to_head); // ������� 2

  const vector<int> expected1 = {5, 4, 1};
  ASSERT_EQUAL(ToVector(list), expected1);

  while (list.GetHead()->next) {
    list.RemoveAfter(list.GetHead());
  }
  ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
  {
    LinkedList<int> list;
    list.PopFront();
  }
  {
    LinkedList<int> list;

    for (int i = 1; i <= 5; ++i) {
      list.PushFront(i);
    }
    for (int i = 1; i <= 5; ++i) {
      list.PopFront();
    }
    ASSERT(list.GetHead() == nullptr);
  }
}

void TestGeneral() {
    LinkedList<int> list;

    for (double i=0; i < 30'000'000; i++) {
        list.PushFront(i);
    }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPushFront);
  RUN_TEST(tr, TestInsertAfter);
  RUN_TEST(tr, TestRemoveAfter);
  RUN_TEST(tr, TestPopFront);
  RUN_TEST(tr, TestGeneral);
  return 0;
}
