#include <algorithm>
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
        end_ = data + size;
    }

    ~SimpleVector() {
        //освободим память! (иначе утечка памяти)
        delete[] data;
    }

    //добавим возможность обращаться к отдельным элементам
    T& operator[](size_t index) {
        return data[index]; //эквивалентно *(data+index);
    }
    //добавим методы begin и end для range based for loop
    //указатель на элемент типа Т
    //указатели на элементы вектора можно использовать в качестве его итераторов
    T* begin() { return data; }
    T* end() { return end_; }
private:
    T* data;
    T* end_;
};

int main() {
    SimpleVector<int> sv(4);
    sv[0] = 5;
    sv[1] = 3;
    sv[2] = 4;
    sv[3] = -1;
    //развернем range based for в обычный цикл for
    for (auto i = sv.begin(); i != sv.end(); ++i) {
        cout << *i << ' ';
    }
    cout << endl;
    sort(sv.begin(), sv.end());
    for (int x : sv) {
        cout << x << ' ';
    }
}