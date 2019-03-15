#include <iostream>
#include <vector>

using namespace std;

//Шаблон класса
template<typename T>
class SimpleVector {
public:
    explicit SimpleVector(size_t size) {
        //выделим в куче блок памяти под 5 обьетов
        data = new T[size];
    }

    ~SimpleVector() {
        //освободим память! (иначе утечка памяти)
        delete[] data;
    }

    //добавим возможность обращаться к отдельным элементам
    T& operator[](size_t index) {
        return data[index]; //эквивалентно *(data+index);
    }

private:
    T* data;
};

int main() {
    SimpleVector<int> sv(5);
    for (int i = 0; i < 5; ++i)
    {
        sv[i] = 5 - i;
    }
    for (int i = 0; i < 5; ++i)
    {
        cout << sv[i] << ' ';
    }
}