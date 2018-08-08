#include <iostream>
#include <exception>
using namespace std;

class Rational {
	// Вставьте сюда реализацию класса Rational
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
			throw invalid_argument("invalid argument");
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

// Вставьте сюда реализацию operator / для класса Rational
Rational operator/(const Rational& one, const Rational& two)
{
	int ch1 = one.Numerator();
	int zn1 = one.Denominator();
	int ch2 = two.Numerator();
	int zn2 = two.Denominator();
	if (ch2 == 0)
	{
		throw domain_error("division by zero!");
	}
	Rational r((ch1*zn2), (zn1*ch2));

	return Rational(r.Numerator(), r.Denominator());
}

int main() {
	try {
		Rational r(1, 0);
		cout << "Doesn't throw in case of zero denominator" << endl;
		return 1;
	}
	catch (invalid_argument& x) {
		cout << x.what() << endl;
	}

	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		cout << "Doesn't throw in case of division by zero" << endl;
		return 2;
	}
	catch (domain_error& x) {
		cout << x.what() << endl;
	}

	cout << "OK" << endl;
	return 0;
}
