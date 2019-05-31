#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Logger {
public:
    //конструктор по умолчанию
    Logger() { cout << "Default ctor\n"; }
    //удалим конструктор копирования
    Logger(const Logger&) = delete;
    //конструктор перемещения
    Logger(Logger&&) { cout << "Move ctor\n"; }
};

Logger MakeLogger() {
    Logger logger;
    // ...
    //возвращение из фунции временного обьекта - copy elision
    return Logger(); // temporary -> returned temporary
    //вот такая оптимизация -> named return value optimization
    return logger;
}

int main() {
    //инициализируем временным обьектом - copy elision
    Logger logger = MakeLogger(); // temporary -> variable

    return 0;
}
