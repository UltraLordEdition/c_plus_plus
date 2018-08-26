#include "stdafx.h"
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};


class Rational {
    // Вставьте сюда реализацию класса Rational из первой части
public:
    Rational() {
        // Реализуйте конструктор по умолчанию
        num = 0;
        dem = 1;
    }

    Rational(int numerator, int denominator) {
        // Реализуйте конструктор
        num = numerator;
        dem = denominator;
        if (num<0 && dem<0)
        {
            num *= -1;
            dem *= -1;
        }
        else if (dem<0)
        {
            dem *= -1;
            num *= -1;
        }
    }

    int nod(const int& new_num, const int& new_dem) const {

        int a, b;
        a = new_num;
        b = new_dem;
        if (a<0 && b<0)
        {
            a *= -1;
            b *= -1;
        }
        else if (a<0)
        {
            a *= -1;
        }
        else if (b<0)
        {
            b *= -1;
        }

        while (a>0 && b>0)
        {
            if (a > b)
            {
                a %= b;
            }
            else {
                b %= a;
            }
        }
        return a + b;
    }

    int Numerator() const {
        // Реализуйте этот метод
        return (num / nod(num, dem));
    }

    int Denominator() const {
        // Реализуйте этот метод
        return (dem / nod(num, dem));
    }

private:
    // Добавьте поля
    int num;
    int dem;
};

// Вставьте сюда реализацию operator == для класса Rational из второй части
bool operator==(const Rational& one, const Rational& two)
{
    return ((one.Numerator() == two.Numerator()) && (one.Denominator() == two.Denominator()));
}

// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а
bool operator<(const Rational& lhs, const Rational& rhs)
{
    double ch1 = lhs.Numerator();
    double zn1 = lhs.Denominator();
    double ch2 = rhs.Numerator();
    double zn2 = rhs.Denominator();

    if ((ch1 / zn1) < (ch2 / zn2))
    {
        return true;
    }
    return false;
}

int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    return 0;
}
