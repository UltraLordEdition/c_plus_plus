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
    //вызываются для не константных методов
    T* begin() { return data; }
    T* end() { return end_; }

    //указатели на константу
    //при передачи по констатным ссылкам или переменные константные
    //
    const T* begin() const { return data; }
    const T* end() const { return end_; }

private:
    T* data;
    T* end_;
};

//функция печати вектора
template<typename T>
void Print(const SimpleVector<T>& v) {
    for(auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << ' ';        
    }
    cout << endl;
}

int main() {
    SimpleVector<int> sv(4);
    sv[0] = 5;
    sv[1] = 3;
    sv[2] = 4;
    sv[3] = -1;
    sort(sv.begin(), sv.end());
    Print(sv);
}