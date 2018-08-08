#include <iostream>
using namespace std;

class Rational {
	// �������� ���� ���������� ������ Rational �� ������ �����
public:
	Rational() {
		// ���������� ����������� �� ���������
		num = 0;
		dem = 1;
	}

	Rational(int numerator, int denominator) {
		// ���������� �����������
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
		// ���������� ���� �����
		return (num / nod(num, dem));
	}

	int Denominator() const {
		// ���������� ���� �����
		return (dem / nod(num, dem));
	}

private:
	// �������� ����
	int num;
	int dem;
};

// �������� ���� ���������� operator == ��� ������ Rational �� ������ �����
bool operator==(const Rational& one, const Rational& two)
{
	return ((one.Numerator() == two.Numerator()) && (one.Denominator() == two.Denominator()));
}
// ���������� ��� ������ Rational ��������� * � /
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

	Rational r((ch1*zn2), (zn1*ch2));

	return Rational(r.Numerator(), r.Denominator());
}

int main() {
	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a * b;
		bool equal = c == Rational(8, 9);
		if (!equal) {
			cout << "2/3 * 4/3 != 8/9" << endl;
			return 1;
		}
	}

	{
		Rational a(5, 4);
		Rational b(15, 8);
		Rational c = a / b;
		bool equal = c == Rational(2, 3);
		if (!equal) {
			cout << "5/4 / 15/8 != 2/3" << endl;
			return 2;
		}
	}
	
	cout << "OK" << endl;
	return 0;
}
