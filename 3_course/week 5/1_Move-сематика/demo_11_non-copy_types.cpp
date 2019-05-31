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

int main() {
    Logger other_logger;
    Logger logger = move(other_logger); //-> вызываем конструктор перемещения

    //Потоки ввода и вывода нельзя копировать -> используем move
    vector<ofstream> streams;
    streams.reserve(5);
    for (int i = 0; i > 5; ++i) {
        ofstream stream(to_string(i) + ".txt");
        stream << "File #" << i << "\n";
        streams.push_back(move(stream));
    }
    for (auto& stream : streams) {
        stream << "Vector is ready!" << endl;
        cout << "Vector is ready!" << endl;
    }
    return 0;
}
