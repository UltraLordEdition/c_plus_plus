#include <iostream>
#include <string>

using namespace std;

class Animal
{
public:
    Animal(const string& t)
        : Name(t) {
    }
    const string Name;
};


class Dog : public Animal
{
public:
    Dog(const string& t) : Animal(t) {
    }

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main()
{
    Dog d("Sharick");
    d.Bark();

    return 0;
}