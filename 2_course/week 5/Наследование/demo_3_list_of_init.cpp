#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

struct  Log
{
    Log(string name) :n(name)
    {
        cout << "+ " << n << endl;
    }
    ~Log()
    {
        cout << "- " << n << endl;
    }

    string n;
};

//�������� ������� ����� �����
struct Fruit
{
    Fruit(const string& t)
        : l(t + " (Fruit)") {
   }
   const string type = "fruit";
   const Log l;
};

//� ������ 10 ������ ��������
struct  Apple : public Fruit    // ������ ����������� �� �������� ������ Fruit
{
    //������� ����������� ������
    Apple(const string& t) : Fruit(t), l(t) {
    }
    const Log l;
};

class AppleTree
{
public:
    AppleTree()
        : a1("a1")
        , a2("a2") {
    }
    Log l = Log("AppleTree");
    Apple a1;
    Apple a2;

};

int main()
{
    AppleTree at;

    return 0;
}

