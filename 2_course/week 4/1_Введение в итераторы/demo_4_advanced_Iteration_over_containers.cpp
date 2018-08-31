#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() 
{
    vector<string> langs = {"Python","C++","C","Java","C#",};
    //Выведем элементы вектора в обратном порядке
    auto it = end(langs);
    while (it != begin(langs))
    {
        --it;
        cout << *it << " ";
    }

    return 0;
}

