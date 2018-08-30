#pragma once

#include <map>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

//Interface
template <class T>
ostream& operator << (ostream& os, const set<T>& s);

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m);

template <class C>
ostream& operator << (ostream& os, const vector<C>& v);

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint);

void Assert(bool b, const string& hint);

class TestRunner
{
public:
    //�������� ������ ������� RunTest, ������� ����� ��������� ���� � ������ ����������
    template <class TestFunc>   //��� ������ ������� ��������� �������!
    void RunTest(TestFunc func, const string& test_name);
    
    //����� ����� ������������� ���������� fail_count
    ~TestRunner();

private:
    //������� ������� ������� ������
    int fail_count = 0;
};

//Implementation

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

template <class C>
ostream& operator << (ostream& os, const vector<C>& v)
{
    os << "{";
    bool first = true;
    for (const auto& x : v)
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

//�������� ������ ������� RunTest, ������� ����� ��������� ���� � ������ ����������
template <class TestFunc>   //��� ������ ������� ��������� �������!
void TestRunner::RunTest(TestFunc func, const string& test_name)
{
    try
    {
        func();
        //���������� �� ������������ ����, ���������� ��� ���� "OK" �� ���� ������
        //cerr ��� ����� � ������������ ����� ������
        cerr << test_name << " OK" << endl;
    }
    catch (runtime_error& e)
    {
        //������� ���������� ������� ������
        ++fail_count;
        cerr << test_name << " fail: " << e.what() << endl;
    }
}
