#include "profile.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string MakeString() {
    return string(100'000'000, 'a');
}

int main() {
    //��������� ���������� 183 ms
    { LOG_DURATION("with variable");
        vector<string> strings;
        string heavy_string = MakeString();     //�������� ����������
        strings.push_back(heavy_string);    //�����������
    }
    //��� �������� ���������� 49 ms (��� �����������)
    { LOG_DURATION("without variable");
        vector<string> strings;
        strings.push_back(MakeString());    //����������� (�������������� ���������)
    }
    //��������� ���������� 108 ms
    { LOG_DURATION("ctor: with variable");
        vector<string> strings;
        string heavy_string = string(100'000'000, 'a');  //�������� ����������
        strings.push_back(heavy_string); //�����������
    }
    //��� �������� ���������� 43 ms (��� �����������)
    { LOG_DURATION("ctor: with variable");
        vector<string> strings;
        strings.push_back(string(100'000'000, 'a'));    //�����������
    }

    return 0;
}
/*
    ��������� ������� ������ ���� �����:
    - ��������� ������ �������: MakeString();
    - ��������� ������ ������������: string(100'000'000, 'a');
*/