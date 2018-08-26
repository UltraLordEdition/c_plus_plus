#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

//�������� ������� ����� �����
struct Fruit
{
    int health = 0;
    //��� ������������� ���� ������
    string type = "fruit";
};

//� ������ 10 ������ ��������
struct  Apple : public Fruit    // ������ ����������� �� �������� ������ Fruit
{
    //������� ����������� ������
    Apple()
    {
        health = 10;
        type = "apple";
    }
};

//� ��������� 5 ������ ��������
struct  Orange : public Fruit
{
    Orange()
    {
        health = 5;
        type = "orange";
    }
};

struct  PineApple : public Fruit
{
    PineApple()
    {
        health = 15;
        type = "papple";
    }
};

class Animal
{
public:
    //������� �����������
    Animal(const string& t = "animal")
        : type(t) {        
    }

    void Eat(const Fruit& f)
    {
        cout << type << " eats " << f.type << ". " << f.health << "hp. " << endl;
    }
/*protected:
    string type = "animal";
*/
 //��� � ������� const
    const string type;
};


//������� ����� �����
class Cat : public Animal
{
public:
    Cat() : Animal("cat"){
    }
    //����� ����� �������, �������� ����� ���
    void Meow() const
    {
        cout << "meow! " << endl;
    }

 };

//������� ������
class Dog : public Animal
{
public:
    Dog() : Animal("dog") {
    }
 };

void DoMeal(Animal& a, Fruit& f)
{
    a.Eat(f);
}

int main()
{
    Cat c;
    Apple a;
    DoMeal(c, a);
    DoMeal(c, a);

    return 0;
}

