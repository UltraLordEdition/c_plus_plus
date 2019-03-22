#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//Ўаблон класса
template<typename T>
class SimpleVector {
public:
    explicit SimpleVector(size_t size) {
        //выделим в куче блок пам€ти под 5 обьетов
        data = new T[size];
        end_ = data + size;
    }

    ~SimpleVector() {
        //освободим пам€ть! (иначе утечка пам€ти)
        delete[] data;
    }

    //добавим возможность обращатьс€ к отдельным элементам
    T& operator[](size_t index) {
        return data[index]; //эквивалентно *(data+index);
    }
    //добавим методы begin и end дл€ range based for loop
    //указатель на элемент типа “
    //указатели на элементы вектора можно использовать в качестве его итераторов
    //вызываютс€ дл€ не константных методов
    T* begin() { return data; }
    T* end() { return end_; }

    //указатели на константу т.е можем изменть указатель, но обьект не можем
    //при передачи по констатным ссылкам или переменные константные
    const T* begin() const { return data; }
    const T* end() const { return end_; }

private:
    T* data;
    T* end_;
};

//функци€ печати вектора
template<typename T>
void Print(const SimpleVector<T>& v) {
    for (auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << ' ';
    }
    cout << endl;
}

int main() {
    int x = 5;
    int* px = &x;
    const int* cpx = &x;
    int* const pxc = &x;
    const int* const cpxc = &x;
    
    //можем все
    *px = 1;
    ++px;

    //указатель на константу
    //*cpx = 1;
    ++cpx;

    //константный указатель
    *pxc = 1;
    //++pxc;

    //константный указатель на константу
    //*cpxc = 1;
    //++cpxc;
}