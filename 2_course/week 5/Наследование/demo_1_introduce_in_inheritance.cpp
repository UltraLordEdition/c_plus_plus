#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

//—оздадим базовый класс фрукт
struct Fruit
{
    int health = 0;
    //дл€ идентификации кого кушаем
    string type = "fruit";
};

//у €блока 10 единиц здоровь€
struct  Apple : public Fruit    // €блоко наследуетс€ от базового класса Fruit
{
    //напишем конструктор €блока
    Apple()
    {
        health = 10;
        type = "apple";
    }
};

//у апельсина 5 единиц здоровь€
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


//обь€вим класс кошки
class Cat : public Animal
{
public:
    Cat()
    {
        type = "cat";
    }
    // ошки умеют м€укать, создадим метод м€у
    void Meow() const
    {
        cout << "meow! " << endl;
    }

 };

//добавим собаку
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
    //создадим кошку
    Cat c;
    //пом€укаем кошкой
    c.Meow();
    //создадим €блоко
    Apple a;
    Orange o;
    Dog d;
    DoMeal(d, a);

    return 0;
}

