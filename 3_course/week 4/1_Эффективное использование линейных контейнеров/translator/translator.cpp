#include "test_runner.h"
#include <string_view>
#include <string>
#include <deque>
#include <map>

using namespace std;

class Translator {
public:
    Translator() {
    }

    void Add(string_view source, string_view target) {
        if (!forward_.count(target) || !backward_.count(source)) {

            words_.push_back(static_cast<string>(source));
            words_.push_back(static_cast<string>(target));
            forward_[words_[words_.size() - 1u]] = words_[words_.size() - 2u];
            backward_[words_[words_.size() - 2u]] = words_[words_.size() - 1u];
        }
    }

    string_view TranslateForward(string_view source) const {
        if (backward_.count(source) != 0) {
            return backward_.at(source);
        }
        else {
            return "";
        }
    }

    string_view TranslateBackward(string_view target) const {
        if (forward_.count(target) != 0) {
            return forward_.at(target);
        }
        else {
            return "";
        }
    }

private:
    map<string_view, string_view> forward_;
    map<string_view, string_view> backward_;
    deque<string> words_;
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));
  translator.Add(string("okno"), string("window"));
  translator.Add(string("AAA"), string("BBB"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
  ASSERT_EQUAL(translator.TranslateForward("AAA"), "BBB");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
