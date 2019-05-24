#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Logger {
public:
    //����������� �� ���������
    Logger() { cout << "Default ctor\n"; }
    //������ ����������� �����������
    Logger(const Logger&) = delete;
    //����������� �����������
    Logger(Logger&&) { cout << "Move ctor\n"; }
};

Logger MakeLogger() {
    Logger logger;
    // ...
    //����������� �� ������ ���������� ������� - copy elision
    return Logger(); // temporary -> returned temporary
    //��� ����� ����������� -> named return value optimization
    return logger;
}

int main() {
    //�������������� ��������� �������� - copy elision
    Logger logger = MakeLogger(); // temporary -> variable

    return 0;
}
