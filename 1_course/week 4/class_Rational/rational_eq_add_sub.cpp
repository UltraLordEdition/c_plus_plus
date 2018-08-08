#include <iostream>
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
	int od = zn1*zn2;

	ch1 = ch1*zn2;
	ch2 = ch2*zn1;
	Rational r((ch1+ch2),od);

	return Rational (r.Numerator(), r.Denominator());
}

Rational operator-(const Rational& one, const Rational& two)
{
	int ch1 = one.Numerator();
	int zn1 = one.Denominator();
	int ch2 = two.Numerator();
	int zn2 = two.Denominator();
	int od = zn1*zn2;

	ch1 = ch1*zn2;
	ch2 = ch2*zn1;
	Rational r((ch1-ch2), od);

	return Rational(r.Numerator(), r.Denominator());
}

int main() {
	{
		Rational r1(4, 6);
		Rational r2(2, 3);
		bool equal = r1 == r2;
		if (!equal) {
			cout << "4/6 != 2/3" << endl;
			return 1;
		}
	}

	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a + b;
		bool equal = c == Rational(2, 1);
		if (!equal) {
			cout << "2/3 + 4/3 != 2" << endl;
			return 2;
		}
	}

	{
		Rational a(5, 7);
		Rational b(2, 9);
		Rational c = a - b;
		bool equal = c == Rational(31, 63);
		if (!equal) {
			cout << "5/7 - 2/9 != 31/63" << endl;
			return 3;
		}
	}

	cout << "OK" << endl;
	return 0;
}
