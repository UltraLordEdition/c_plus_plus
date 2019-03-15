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

private:
    T* data;
};

int main() {
    SimpleVector<int> sv(5);
}