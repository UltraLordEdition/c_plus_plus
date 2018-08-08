#include "stdafx.h"
#include <cassert>
#include <iostream>
#include <string>
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

void TestAddSynonyms()
{
    {
        Synonyms empty;
        //Создали синонимы
        AddSynomyns(empty, "a", "b");
        //Ожидаем от функции
        const Synonyms expected = {
            {"a",{"b"}},
            {"b",{"a"}},
        };
        //Формируем наши ожидания используя assert
        assert(empty == expected);
    }
    {
        Synonyms synonyms = {
            {"a", {"b"}},
            {"b", {"a", "c"}},
            {"c", {"b"}}
        };
        AddSynomyns(synonyms, "a", "c");
        const Synonyms expected = {
            { "a",{ "b", "c" }},
            { "b",{ "a", "c" }},
            { "c",{ "b", "a" }}
        };
        assert(synonyms == expected);
    }
    cout << "TestAddSynonyms OK" << endl;
}

void TestCount()
{
    
    {
        Synonyms empty;
        assert(GetSynonymCount(empty, "a") == 0);
    }
    {
        Synonyms synonyms = {
            { "a",{ "b", "c" }},
            { "b",{ "a" }},
            { "c",{ "a" }}
        };
        assert(GetSynonymCount(synonyms, "a") == 2);
        assert(GetSynonymCount(synonyms, "b") == 1);
        assert(GetSynonymCount(synonyms, "z") == 0);
    }
    cout << "TestCount OK" << endl;
}

void TestAreSynonyms()
{
    {
        Synonyms empty;
        assert(!AreSynonyms(empty, "a", "b"));
        assert(!AreSynonyms(empty, "b", "a"));
    }
    {
        Synonyms synonyms = {
            { "a", { "b", "c" }},
            { "b", { "a" }},
            { "c", { "a" }}
        };
        assert(AreSynonyms(synonyms, "a", "b"));
        assert(AreSynonyms(synonyms, "b", "a"));
        assert(AreSynonyms(synonyms, "a", "c"));
        assert(AreSynonyms(synonyms, "c", "a"));
        assert(!AreSynonyms(synonyms, "b", "c"));
        assert(!AreSynonyms(synonyms, "c", "b"));
    }
    cout << "TestAreSynonyms OK" << endl;
}

void TestAll()
{
    TestCount();
    TestAreSynonyms();
    TestAddSynonyms();    
}

int main() {
    TestAll();
    return 0;

    int q;
    cin >> q;

    Synonyms synonyms;

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "ADD") {

            string first_word, second_word;
            cin >> first_word >> second_word;
            //Вызов функции
            AddSynomyns(synonyms, first_word, second_word);
        }
        else if (operation_code == "COUNT") {

            string word;
            cin >> word;
            cout << GetSynonymCount(synonyms, word) << endl;

        }
        else if (operation_code == "CHECK") {

            string first_word, second_word;
            cin >> first_word >> second_word;

            // ищём второе слово во множестве синонимов первого
            // (можно было сделать и наоборот)
            if (AreSynonyms(synonyms, first_word, second_word)) {
                cout << "YES" << endl;
            }
            else {
                cout << "NO" << endl;
            }

        }
    }

    return 0;
}