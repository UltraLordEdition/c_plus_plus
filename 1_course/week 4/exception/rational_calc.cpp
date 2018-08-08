#include <iostream>
#include <sstream>
#include <exception>
#include <vector>
#include <set>
#include <map>

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
		if (denominator == 0)
		{
			throw invalid_argument("Invalid argument");
		}
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

// Реализуйте для класса Rational операторы ==, + и -
bool operator==(const Rational& one, const Rational& two)
{
	return ((one.Numerator() == two.Numerator()) && (one.Denominator() == two.Denominator()));
}

Rational operator+(const Rational& one, const Rational& two)
{
	int ch1 = one.Numerator();
	int zn1 = one.Denominator();
	int ch2 = two.Numerator();
	int zn2 = two.Denominator();
	int od = zn1 * zn2;

	ch1 = ch1 * zn2;
	ch2 = ch2 * zn1;
	Rational r((ch1 + ch2), od);

	return Rational(r.Numerator(), r.Denominator());
}

Rational operator-(const Rational& one, const Rational& two)
{
	int ch1 = one.Numerator();
	int zn1 = one.Denominator();
	int ch2 = two.Numerator();
	int zn2 = two.Denominator();
	int od = zn1 * zn2;

	ch1 = ch1 * zn2;
	ch2 = ch2 * zn1;
	Rational r((ch1 - ch2), od);

	return Rational(r.Numerator(), r.Denominator());
}

// Реализуйте для класса Rational операторы * и /
Rational operator*(const Rational& one, const Rational& two)
{
	int ch1 = one.Numerator();
	int zn1 = one.Denominator();
	int ch2 = two.Numerator();
	int zn2 = two.Denominator();

	Rational r((ch1*ch2), (zn1*zn2));

	return Rational(r.Numerator(), r.Denominator());
}

Rational operator/(const Rational& one, const Rational& two)
{
	int ch1 = one.Numerator();
	int zn1 = one.Denominator();
	int ch2 = two.Numerator();
	int zn2 = two.Denominator();
	if (ch2 == 0)
	{
		throw domain_error("Division by zero");
	}
	Rational r((ch1*zn2), (zn1*ch2));

	return Rational(r.Numerator(), r.Denominator());
}

// Реализуйте для класса Rational операторы << и >>
ostream& operator<<(ostream& stream, const Rational& rational)
{
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}

istream& operator>>(istream& stream, Rational& rational)
{
	int num = 0, den = 1;
	string line;
	stream >> line;

	if (!line.empty())
	{
		stringstream str;
		str << line;
		str >> num;
		str.ignore(1);
		str >> den;
		rational = { num,den };
	}
	return stream;
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
	Rational r1, r2;
	char sumbol;
	try {
		cin >> r1 >> sumbol >> r2;
	}
	catch (invalid_argument& x) {
	cout << x.what() << endl;
	sumbol = NULL;
	}
	if (sumbol == '+')
	{
		cout << r1 + r2 << endl;
	}
	else if (sumbol == '-')
	{
		cout << r1 - r2 << endl;
	}
	else if (sumbol == '*')
	{
		cout << r1 * r2 << endl;
	}
	else if (sumbol == '/')
	{
		try {
				cout << r1 / r2 << endl;
			}
			catch (domain_error& x) {
				cout << x.what() << endl;
			}
	}

	return 0;
}
