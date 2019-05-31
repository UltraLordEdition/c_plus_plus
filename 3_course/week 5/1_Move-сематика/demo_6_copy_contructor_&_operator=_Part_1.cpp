#include <iostream>
#include <vector>

using namespace std;

class Logger {
public:
    //����������� �� ���������
    Logger() { cout << "Default ctor\n"; }

    //����������� �����������
    Logger(const Logger&) { cout << "Copy ctor\n"; }

    //�������� ������������
    void operator=(const Logger&) { cout << "Copy assigment\n"; }
};

int main() {
    Logger source;              //"Default ctor"
    Logger target = source;     //"Copy ctor"

    //����������� target �� ������� �������
    vector<Logger> loggers;
    loggers.push_back(target);  //"Copy ctor"

    //�������� ������������
    source = target;            //"Copy assigment"

    return 0;
}
