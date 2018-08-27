#pragma once

#include <map>
#include <set>
using namespace std;

using Synonyms = map<string, set<string>>;

//Interface

void AddSynomyns(Synonyms& synonyms, const string& first_word, const string& second_word);
size_t GetSynonymCount(Synonyms& synonyms, const string& first_word);
bool AreSynonyms(Synonyms& synonyms, const string& first_word, const string& second_word);
