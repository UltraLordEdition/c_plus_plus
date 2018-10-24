#pragma once

#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//��������� �������� ������ ��� vector
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
//template AssertEqual in all unit-tests
inline void Assert(bool b, const string& hint)
{
	AssertEqual(b, true, hint);
}

//�������� RunTest � �����
class TestRunner
{
public:
	//�������� ������ ������� RunTest, ������� ����� ��������� ���� � ������ ����������
	template <class TestFunc>   //��� ������ ������� ��������� �������!
	void RunTest(TestFunc func, const string& test_name)
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
	//����� ����� ������������� ���������� fail_count
	~TestRunner()
	{
		if (fail_count > 0)
		{
			cerr << fail_count << " tests failed. Terminate";
			//�������� ���������� ��������� � ���������� � ��� ����� ��������
			//��� �������� �
			exit(1);
		}
	}

private:
	//������� ������� ������� ������
	int fail_count = 0;
};
