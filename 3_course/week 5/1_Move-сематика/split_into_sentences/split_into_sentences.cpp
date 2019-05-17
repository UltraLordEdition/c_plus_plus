#include "test_runner.h"
#include "profile.h"

#include <iterator>
#include <vector>
#include <utility>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) { 
  // Напишите реализацию функции, не копируя объекты типа Token
    vector<Sentence<Token>> text;
    if (tokens.empty()) {
        text.push_back(move(tokens));
        return text;
    }
    Sentence<Token> sentence;
    size_t count = 0u;
    for (Token& word : tokens) {
        if (word.IsEndSentencePunctuation()) {
            count++;
        }
        else {
            if (count > 1u) {
                text.push_back(move(sentence));
                sentence.clear();
            }
            count = 0u;
        }
        sentence.push_back(move(word));
    }
    if (!sentence.empty()) {
        text.push_back(move(sentence));
    }
    return text;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );
  
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true} })),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}, {".", true} })),
      vector<Sentence<TestToken>>({
          {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
          {{"Without"}, {"copies"}, {".", true}, {".", true}},
      })
  );
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({ {"!", true}, {"!", true} })),
      vector<Sentence<TestToken>>({ {{"!", true}, {"!", true}} })
  );
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({ {"!", true}, {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}, {".", true} })),
      vector<Sentence<TestToken>>({
          {{"!", true}, {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
          {{"Without"}, {"copies"}, {".", true}, {".", true}},
      })
  );
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({ {"!", true}, {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"} })),
      vector<Sentence<TestToken>>({
          {{"!", true}, {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
          {{"Without"}, {"copies"}},
      })
  );
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({ {"!", true}, {"!", true}, {"!", true}, {"!", true}, {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"} })),
      vector<Sentence<TestToken>>({
          {{"!", true}, {"!", true}, {"!", true}, {"!", true}},
          {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
          {{"Without"}, {"copies"}},
      })
  );
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({ {"!", true}, {"!", true}, {"!", true}, {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"} })),
      vector<Sentence<TestToken>>({
          {{"!", true}, {"!", true}, {"!", true}},
          {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
          {{"Without"}, {"copies"}},
      })
  );
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({ {"!", true}, {"!", true}, {"!", true}, {"!", true}, {"A"}, {"B"}, {"!", true}, {"C"}, {"!", true}, {"!", true}, {"A"}, {"!", true} })),
      vector<Sentence<TestToken>>({
          {{"!", true}, {"!", true}, {"!", true}, {"!", true}},
          {{"A"}, {"B"}, {"!", true}, {"C"}, {"!", true}, {"!", true}},
          {{"A"}, {"!", true}}
      })
  );
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({ {"!", true}, {"!", true}, {"!", true}, {"A"}, {"B"}, {"!", true}, {"C"}, {"!", true}, {"!", true}, {"!", true}, {"D"}, {"D"}, {"D"}})),
      vector<Sentence<TestToken>>({
          {{"!", true}, {"!", true}, {"!", true}},
          {{"A"}, {"B"}, {"!", true}, {"C"}, {"!", true}, {"!", true}, {"!", true}},
          {{"D"}, {"D"}, {"D"}}
      })
  );
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({ {"!", true}, {"!", true}, {"!", true}, {"A"} })),
      vector<Sentence<TestToken>>({
          {{"!", true}, {"!", true}, {"!", true}},
          {{"A"}}
      })
  );
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({ {"A"}, {"A"}, {"A"}, {"!", true}, {"!", true}, {"A"} })),
      vector<Sentence<TestToken>>({
          {{"A"}, {"A"}, {"A"}, {"!", true}, {"!", true}},
          {{"A"}}
      })
  );
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({ {"!", true}, {"A"}, {"A"}, {"!", true}, {"S"}, {"A"} })),
      vector<Sentence<TestToken>>({
          {{"!", true}, {"A"}, {"A"}, {"!", true}, {"S"}, {"A"}}
      })
  );
  ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({ {"A"} })), vector<Sentence<TestToken>>({ {{"A"}} }));
  ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({ {"!", true} })), vector<Sentence<TestToken>>({ {{"!", true}} }));
  ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({ {"!", true}, {"!", true} })), vector<Sentence<TestToken>>({ {{"!", true}, {"!", true}} }));
  ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({ {"!", true}, {".", true} })), vector<Sentence<TestToken>>({ {{"!", true}, {".", true}} }));
  ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({ {"!", true}, {"!", true}, {"!", true} })), vector<Sentence<TestToken>>({ {{"!", true}, {"!", true}, {"!", true}} }));
 // ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({ {""} })), vector<Sentence<TestToken>>({ {{""}} }));
 // ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({ {{}} })), vector<Sentence<TestToken>>({ {{}} }));
  ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({ {} })), vector<Sentence<TestToken>>({ {{"", false}} }));
 // ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({ })), vector<Sentence<TestToken>>({ }));
}

int main() {
    TestToken t;
    TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
