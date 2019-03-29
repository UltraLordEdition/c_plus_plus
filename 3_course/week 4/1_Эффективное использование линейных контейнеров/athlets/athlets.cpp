//#include "test_runner.h"
#include <iostream>
#include <list>
#include <map>

using namespace std;

class Sportsman {
public:

    Sportsman() {
    }

    void Insert(int sportsman, int pos) {
        if (sportsmans_.count(pos)) {
            sportsmans_[sportsman] = position_.insert(sportsmans_[pos], sportsman);
        }
        else {
            sportsmans_[sportsman] = position_.insert(end(position_), sportsman);
        }
    }

    list<int>& Position() {
        return position_;
    }

private:

    list<int> position_;
    map<int, list<int>::iterator> sportsmans_;
};


/*
void TestAll() {
  {
    Sportsman s;

    s.Insert(42, 0);
    s.Insert(17, 42);
    s.Insert(13, 0);
    s.Insert(123, 42);
    s.Insert(5, 13);
    const list<int> l = { 17, 123, 42, 5, 13 };
    ASSERT_EQUAL(s.Position(), l);
  }
  {
     Sportsman s;

     s.Insert(42, 0);
     s.Insert(17, 42);
     s.Insert(13, 0);
     s.Insert(123, 42);
     s.Insert(5, 13);
     s.Insert(45, 50);
     s.Insert(46, 45);
     s.Insert(3, 17);
     const list<int> l = { 3, 17, 123, 42, 5, 13, 46, 45 };
     ASSERT_EQUAL(s.Position(), l);
  }
}*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //TestRunner tr;
    //RUN_TEST(tr, TestAll);

    int n = 5;
    cin >> n;
    Sportsman s;

    for (int i = 0; i < n; i++) {
        int sportsman, link_sportsman;
        cin >> sportsman >> link_sportsman;
        s.Insert(sportsman, link_sportsman);
    }

    for (const auto& i : s.Position()) {
        cout << i << " ";
    }

    return 0;
}