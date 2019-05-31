#include "profile.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string MakeString() {
    return string(100'000'000, 'a');
}

int main() {
    //временная переменная 183 ms
    { LOG_DURATION("with variable");
        vector<string> strings;
        string heavy_string = MakeString();     //врменная переменная
        strings.push_back(heavy_string);    //копирование
    }
    //без врменной переменной 49 ms (нет копирования)
    { LOG_DURATION("without variable");
        vector<string> strings;
        strings.push_back(MakeString());    //перемещение (перенаправляет указатель)
    }
    //временная переменная 108 ms
    { LOG_DURATION("ctor: with variable");
        vector<string> strings;
        string heavy_string = string(100'000'000, 'a');  //врменная переменная
        strings.push_back(heavy_string); //копирование
    }
    //без врменной переменной 43 ms (нет копирования)
    { LOG_DURATION("ctor: with variable");
        vector<string> strings;
        strings.push_back(string(100'000'000, 'a'));    //перемещение
    }

    return 0;
}
/*
    Временные обьекты бывают двух типов:
    - результат вызова функции: MakeString();
    - результат вызова конструктора: string(100'000'000, 'a');
*/