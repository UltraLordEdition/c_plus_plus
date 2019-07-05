#include "test_runner.h"
#include "profile.h"
#include <future>
#include <functional>
#include <vector>
#include <map>
#include <string>
#include <string_view>
using namespace std;

template <typename It>
string ConstructString(It range_begin, It range_end)
{
    string word(range_begin, range_end);
    return word;
}

vector<string> SplitIntoWords(const string& s)
{
    vector<string> words;
    auto start_it = begin(s);
    while (true)
    {
        auto end_it = find((start_it), end(s), ' ');
        words.push_back(ConstructString(start_it, end_it));
        if (end_it != end(s))
        {
            start_it = end_it;
            ++start_it;
        }
        else
        {
            return words;
        }
    }
}

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for (const auto&[key, value] : other.word_frequences) {
            if (word_frequences.count(key)) {
                word_frequences[key] += value;
            }
            word_frequences.insert({ key,value });
        }
    }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats stats;
    vector<string> words = SplitIntoWords(line);
    for (const auto& v : words) {
        if (key_words.count(v)) {
            stats.word_frequences[v]++;
        }
    }
    return stats;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input) {
    LOG_DURATION("ExploreKeyWordsSingleThread");
    Stats result;
    for (string line; getline(input, line); ) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWordsSingle(const set<string>& key_words, istream& input) {
    return ExploreKeyWordsSingleThread(key_words, input);
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    // Реализуйте эту функцию
    LOG_DURATION("ExploreKeyWords");
    size_t treads = 4;
    vector<string> str;
    vector<future<Stats>> futures;
    Stats result;
    { LOG_DURATION("getline -> vector<string>");
        for (string line; getline(input, line); ) {
            str.push_back(move(line));
        }
    }
    size_t sizeTread = str.size() / treads;
    vector<stringstream> pages(treads);
    { LOG_DURATION("preparing treads");
        for (size_t i = 0, j = 0; i < str.size(); i++) {
            pages[j] << ' ' << str[i];
            
            if (i > sizeTread) {
                sizeTread += str.size() / treads;
                j++;
            }
        }
    }
    { LOG_DURATION("sum");
        for (auto& page : pages) {
            futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(page)));
        }
        for (auto& f : futures) {
            result += f.get();
        }
    }
    return move(result);
}

void TestBasic() {
    const set<string> key_words = { "yangle", "rocks", "sucks", "all" };

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
      {"yangle", 6},
      {"rocks", 2},
      {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

//функция генерирующая ключевые слова
set<string> GenerateKeyWords() {
    LOG_DURATION("GenerateKeyWords");
    set<string>  KeyWords;
    const int SIZE = 50000;
    for (int i = 0; i < SIZE; ++i) {
        KeyWords.insert(to_string(i));
    }
    KeyWords.insert("aaaa");
    return KeyWords;
}

//функция генерирующая текст
string GenerateText() {
    //LOG_DURATION("GenerateText");
    const int SIZE = 10000000;
    string text(SIZE, 'a');
    for (int i = 0; i < SIZE; i += 5) {
        text[i] = ' ';
    }
    for (int i = 0; i < SIZE; i += 20) {
        if (i != 0) {
            text[i] = '\n';
        }
    }
    return text;
}

void TestSpeedSingleTread() {
    LOG_DURATION("TestSpeedSingleTread");
    const set<string> key_words = GenerateKeyWords();
    stringstream ss;
    ss << GenerateText();
    const auto stats = ExploreKeyWordsSingle(key_words, ss);
    const map<string, int> expected = {
        {"aaaa", 2000000}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

void TestSpeedMultiTread() {
    LOG_DURATION("TestSpeedMultiTread");
    const set<string> key_words = GenerateKeyWords();
    stringstream ss;
    ss << GenerateText();
    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"aaaa", 2000000}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
    RUN_TEST(tr, TestSpeedSingleTread);
    RUN_TEST(tr, TestSpeedMultiTread);
}
