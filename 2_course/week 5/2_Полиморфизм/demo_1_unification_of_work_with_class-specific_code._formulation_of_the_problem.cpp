#include "stdafx.h"
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

    void Voice() const
    {
        if (type_ == "cat")
        {
            cout << "Meow!" << endl;
        }
        else if (type_ == "dog")
        {
            cout << "Whaf!" << endl;
        }
        else if (type_ == "parrot")
        {
            cout << name_ << " is good!" << endl;
        }
    }

private:
    const string type_;
};

class Cat : public Animal
{
public:
    Cat() : Animal("cat") {}    
};

class Dog : public Animal
{
public:
    Dog() : Animal("dog") {}    
};

class Parrot : public Animal
{
public:
    Parrot(const string& name) : Animal("parrot"), name_(name) {}       

private:
    const string& name_;
};

void MakeSound(const Animal& a)
{
    a.Voice();
}

int main()
{
    Cat c;
    Dog d;

    c.Eat("apple");
    d.Eat("orange");

    MakeSound(c);
    MakeSound(d);

    return 0;
}