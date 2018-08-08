#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

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
		
	if ((ch1/zn1) < (ch2/zn2))
	{
		return true;
	}
	return false;
}

int main() {
	{
		const set<Rational> rs = { { 1, 2 },{ 1, 25 },{ 3, 4 },{ 3, 4 },{ 1, 2 } };
		if (rs.size() != 3) {
			cout << "Wrong amount of items in the set" << endl;
			return 1;
		}
		
		vector<Rational> v;
		for (auto x : rs) {
			v.push_back(x);
		}
		if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
			cout << "Rationals comparison works incorrectly" << endl;
			return 2;
		}
	}
	
	{
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];


		++count[{2, 3}];

		if (count.size() != 2) {
			cout << "Wrong amount of items in the map" << endl;
			return 3;
		}
	}
	
	{
		set<Rational> rationals;
		rationals.insert(Rational(1, 2));
		rationals.insert(Rational(1, 3));

		for (auto& x : rationals)
		{
			cout << x.Numerator() << "/" << x.Denominator() << endl;
		}

		map<Rational, string> name;
		name[Rational(1, 2)] = "одна вторая";
	}
	cout << "OK" << endl;
	return 0;
}
