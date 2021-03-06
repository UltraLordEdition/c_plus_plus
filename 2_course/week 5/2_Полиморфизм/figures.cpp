#include <iostream>
#include <sstream>
#include <memory>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Figure
{
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure
{
public:
    Triangle(const double& a, const double& b, const double& c) : a_(a), b_(b), c_(c)
    {
    }

    string Name() const override
    {
        return "TRIANGLE";
    }

    double Perimeter() const override
    {
        return (a_ + b_ + c_);
    }

    double Area() const override
    {
        return sqrt(p_*(p_ - a_)*(p_ - b_)*(p_ - c_));
    }

private:
    const double a_, b_, c_;
    const double p_ = (a_ + b_ + c_) / 2;
};

class Rect : public Figure
{
public:
    Rect(const double& l, const double& w) : l_(l), w_(w)
    {
    }

    string Name() const override
    {
        return "RECT";
    }

    double Perimeter() const override
    {
        return 2 * (l_ + w_);
    }

    double Area() const override
    {
        return l_ * w_;
    }

private:
    const double l_, w_;
};

class Circle : public Figure
{
public:
    Circle(const double& r) : r_(r)
    {
    }

    string Name() const override
    {
        return "CIRCLE";
    }

    double Perimeter() const override
    {
        return 2 * PI*r_;
    }

    double Area() const override
    {
        return PI * (r_*r_);
    }

private:
    const double r_;
    const double PI = 3.14;
};

shared_ptr<Figure> CreateFigure(istringstream& name_line)
{
    string figura;
    name_line >> figura;
    double a, b, c;

    name_line >> a;
    if (figura == "CIRCLE")
    {
       
        return make_shared<Circle>(a);
    }
    else if (figura == "RECT")
    {
        name_line >> b;
        return make_shared<Rect>(a, b);
    }
    else if (figura == "TRIANGLE")
    {
        name_line >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
}

int main()
{
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); )
    {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD")
        {
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT")
        {
            for (const auto& current_figure : figures)
            {
                cout << fixed << setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}