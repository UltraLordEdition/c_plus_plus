#include <iostream>
#include <sstream>

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
// Реализуйте для класса Rational операторы << и >>
ostream& operator<<(ostream& stream, const Rational& rational)
{
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}

istream& operator>>(istream& stream, Rational& rational)
{
	int num=0, den=1;
	string line;
	stream >> line;

	if (!line.empty())
	{
		stringstream str;
		str << line;
		str >> num;
		str.ignore(1);
		str >> den;
		rational = {num,den};
	}
	return stream;
}

int main() {
	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 3;
		}


		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 4;
		}
	}

	cout << "OK" << endl;
	return 0;
}
