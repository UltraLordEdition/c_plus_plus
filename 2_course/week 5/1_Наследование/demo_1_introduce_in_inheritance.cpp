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
    void Eat(const Fruit& f)
    {
        cout << type << " eats " << f.type << ". " << f.health << "hp. " << endl;
    }
    string type = "animal";
};


//������� ����� �����
class Cat : public Animal
{
public:
    Cat()
    {
        type = "cat";
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
    Dog()
    {
        type = "dog";
    }
 };

void DoMeal(Animal& a, Fruit& f)
{
    a.Eat(f);
}

int main()
{
    //�������� �����
    Cat c;
    //��������� ������
    c.Meow();
    //�������� ������
    Apple a;
    Orange o;
    Dog d;
    DoMeal(d, a);

    return 0;
}

