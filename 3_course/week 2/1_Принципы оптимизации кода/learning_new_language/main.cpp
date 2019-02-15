#include "profile.h"
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>

using namespace std;

class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string>& words) {
        LOG_DURATION("Learn");
        int newWords = 0;
        for (const auto& word : words) {
            if (dict.find(word) == dict.end()) {
                ++newWords;
                dict.insert(word);
            }            
        }
        return newWords;
    }

    vector<string> KnownWords() {
        LOG_DURATION("KnownWords");       
        return {dict.begin(), dict.end()};
    }
};

/*
class Learner {
private:
    vector<string> dict;

public:
    int Learn(const vector<string>& words) {
        LOG_DURATION("Learn");
        int newWords = 0;
        for (const auto& word : words) {
            if (find(dict.begin(), dict.end(), word) == dict.end()) {
                ++newWords;
                dict.push_back(word);
            }
        }
        return newWords;
    }

    vector<string> KnownWords() {
        LOG_DURATION("KnownWords");
        sort(dict.begin(), dict.end());
        dict.erase(unique(dict.begin(), dict.end()), dict.end());
        return dict;
    }
};
*/
int main() {
    LOG_DURATION("In total");
    Learner learner;
    //stringstream sstr;
    //sstr << "hello hello world good bye world good bye";
    string line;
    unsigned int i = 0;
    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";               
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}