#pragma once

#include <map>
#include <set>
using namespace std;

using Synonyms = map<string, set<string>>;

void AddSynomyns(Synonyms& synonyms, const string& first_word, const string& second_word)
{
	// второе слово добавляем в список синонимов первого...
	synonyms[first_word].insert(second_word);
	// и наоборот
	synonyms[second_word].insert(first_word);
}

size_t GetSynonymCount(Synonyms& synonyms, const string& first_word)
{
	return synonyms[first_word].size();
}

bool AreSynonyms(Synonyms& synonyms, const string& first_word, const string& second_word)
{
	return synonyms[first_word].count(second_word) == 1;
}
