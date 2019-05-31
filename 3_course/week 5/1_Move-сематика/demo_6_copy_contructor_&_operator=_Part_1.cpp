#include <iostream>
#include <vector>

using namespace std;

class Logger {
public:
    //конструктор по умолчанию
    Logger() { cout << "Default ctor\n"; }

    //конструктор копирования
    Logger(const Logger&) { cout << "Copy ctor\n"; }

    //оператор присваивания
    void operator=(const Logger&) { cout << "Copy assigment\n"; }
};

int main() {
    Logger source;              //"Default ctor"
    Logger target = source;     //"Copy ctor"

    //копирование target во внуторь вектора
    vector<Logger> loggers;
    loggers.push_back(target);  //"Copy ctor"

    //оператор присваивания
    source = target;            //"Copy assigment"

    return 0;
}
