#include <iostream>
#include <string>

using namespace std;

class Animal
{
public:
    Animal(const string& type) : type_(type) {}

    void Eat(const string& fruit)
    {
        cout << type_ << " eats " << fruit << endl;
    }

    // virtual говорим базовому классу, что в потомках может быть реализация метода Voice() с точно такой же сигнатурой
    // возвращаемый тип и константность должны совпадать
    virtual void Sound() const {}

private:
    const string type_;
};

class Cat : public Animal
{
public:
    Cat() : Animal("cat") {}    

    //Добавим в каждый класс 
    // override добавляется к методам в производных классах
    // требует объявления метода в базовом классе с такой же сигнатурой
    // позволяет заметить компилятору ошибку если были удалены методы базового класса
    void Sound() const override
    {
        cout << "Meow!" << endl;
    }
};

class Dog : public Animal
{
public:
    Dog() : Animal("dog") {}    

    //Добавим в каждый класс
    void Sound() const override
    {
        cout << "Whaf!" << endl;
    }
};

class Parrot : public Animal
{
public:
    Parrot(const string& name) : Animal("parrot"), name_(name) {}  

    //Добавим в каждый класс
    void Sound() const override
    {
        cout << name_ << " is good!" << endl;
    }

private:
    const string name_;
};

void MakeSound(const Animal& a)
{
    a.Sound();
}

int main()
{
    Cat c;
    Dog d;

    // Добавим попугая и поверим
    Parrot p("Kesha");
    
    MakeSound(c);
    MakeSound(d);
    MakeSound(p);
       
    return 0;
}