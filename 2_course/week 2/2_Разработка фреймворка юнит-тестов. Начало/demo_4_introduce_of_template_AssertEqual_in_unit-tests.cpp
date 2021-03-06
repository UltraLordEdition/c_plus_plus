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
    // ������ ����� ��������� � ������ ��������� �������...
    synonyms[first_word].insert(second_word);
    // � ��������
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

//��������� �������� ������ ��� set
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

//��������� �������� ������ ��� map
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
//������ template AssertEqual in all unit-tests
void Assert(bool b, const string& hint)
{
    AssertEqual(b, true, hint);
}

void TestAddSynonyms()
{
    {
        Synonyms empty;
        //������� ��������
        AddSynomyns(empty, "a", "b");
        //������� �� �������
        const Synonyms expected = {
            {"a",{"b"}},
            {"b",{"a"}},
        };
        //��������� ���� �������� ��������� assert
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
    cout << "TestAddSynonyms OK" << endl;
}

void TestCount()
{
    
    {
        Synonyms empty;
        //������� ���������� ������� Hint ��� ������������� ������������ assert
        //������ ��� ������ �������� ���������� "u" �.�. ���� ��������� ����������� �� �������� �����
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
    cout << "TestCount OK" << endl;
}
//�������� ��� �����
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
    cout << "TestAreSynonyms OK" << endl;
}

void TestAll()
{
    TestAreSynonyms();
    TestCount();
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
            //����� �������
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

            // ���� ������ ����� �� ��������� ��������� �������
            // (����� ���� ������� � ��������)
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