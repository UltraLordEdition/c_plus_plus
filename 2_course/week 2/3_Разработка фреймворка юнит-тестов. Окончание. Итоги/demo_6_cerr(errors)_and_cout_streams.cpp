#include "stdafx.h"
#include <cassert>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <exception>
#include <sstream>

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

//Шаблонный оператор вывода для set
template <class T>
ostream& operator << (ostream& os, const set<T>& s)
{
    os << "{";
    bool first = true;
    for (const auto& x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

//Шаблонный оператор вывода для map
template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m)
{
    os << "{";
    bool first = true;
    for (const auto& kv : m)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint)
{
    if (t != u)
    {
        ostringstream os;
        os << "Assert failed: " << t << " != " << u << " Hint: " << hint;
        throw runtime_error(os.str());
    }
}
//template AssertEqual in all unit-tests
void Assert(bool b, const string& hint)
{
    AssertEqual(b, true, hint);
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
        AssertEqual(empty, expected, "Add to empty");
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
        AssertEqual(synonyms, expected, "Add to non-empty");
    }
}

void TestCount()
{
    
    {
        Synonyms empty;
        //Добавим уникальную строчку Hint для идентификации сработавшего assert
        //Укажем что второй параметр безнаковый "u" т.к. идет сравнение безнакового со знаковым типом
        AssertEqual(GetSynonymCount(empty, "a"), 0u, "count for empty");
    }
    {
        Synonyms synonyms = {
            { "a",{ "b", "c" }},
            { "b",{ "a" }},
            { "c",{ "a" }}
        };
        AssertEqual(GetSynonymCount(synonyms, "a"), 2u, "count for a");
        AssertEqual(GetSynonymCount(synonyms, "b"), 1u, "count for b");
        AssertEqual(GetSynonymCount(synonyms, "z"), 0u, "count for z");
    }
}
//Поправим код здесь
void TestAreSynonyms()
{
    {
        Synonyms empty;
        Assert(!AreSynonyms(empty, "a", "b"), "empty a b");
        Assert(!AreSynonyms(empty, "b", "a"), "empty b a");
    }
    {
        Synonyms synonyms = {
            { "a", { "b", "c" }},
            { "b", { "a" }},
            { "c", { "a" }}
        };
        Assert(AreSynonyms(synonyms, "a", "b"), "empty a b");
        Assert(AreSynonyms(synonyms, "b", "a"), "empty b a");
        Assert(AreSynonyms(synonyms, "a", "c"), "empty a c");
        Assert(AreSynonyms(synonyms, "c", "a"), "empty c a");
        Assert(!AreSynonyms(synonyms, "b", "c"), "empty b c");
        Assert(!AreSynonyms(synonyms, "c", "b"), "empty c b");
    }    
}

//Создадим шаблон функции RunTest, который будет запускать тест и ловить исключения
template <class TestFunc>   //это шаблон который принимает функцию!
void RunTest(TestFunc func, const string& test_name)
{
    try
    {
        func();
        //избавились от дублирования кода, говорящего что тест "OK" во всех тестах
        //cerr это вывод в сстандартный поток ошибок
        cerr << test_name << " OK" << endl;
    }
    catch (runtime_error& e)
    {
        cerr << test_name << " fail: " << e.what() << endl;
    }
}

void TestAll()
{
    RunTest(TestAreSynonyms, "TestAreSynonyms");
    RunTest(TestCount,"TestCount");
    RunTest(TestAddSynonyms,"TestAddSynonyms");
}

int main() {
    TestAll();
        
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