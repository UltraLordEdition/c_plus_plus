#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    //конструктор от размера
    explicit SimpleVector(size_t size);
    //конструктор копирования = перемещению если мы не написали конструктор перемещения
    SimpleVector(const SimpleVector& other);
    //конструктор перемещения
    //rvalue reference - позволяет принимать временные обьекты
    SimpleVector(SimpleVector&& other);
    ~SimpleVector();

    T& operator[](size_t index);

    T* begin();
    T* end();

    const T* begin() const;
    const T* end() const;


    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);

    //оператор копирующего присваивания
    void operator=(const SimpleVector& other);

    //оператор перемещающего присваивания
    void operator=(SimpleVector&& other);

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

template <typename T>
SimpleVector<T>::SimpleVector(size_t size)
    : data(new T[size])
    , size(size)
    , capacity(size)
{
}

//реализуем конструктор копирования
template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T>& other)
//выделим новую память, под новый обьект
//пронициализировать остальные поля
    : data(new T[other.capacity])
    , size(other.size)
    , capacity(other.capacity)
{
    //и заполнить эти данные
    copy(other.begin(), other.end(), begin());
}

template <typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] data;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
size_t SimpleVector<T>::Size() const {
    return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
    return capacity;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
    if (size >= capacity) {
        auto new_cap = capacity == 0 ? 1 : 2 * capacity;
        auto new_data = new T[new_cap];
        copy(begin(), end(), new_data);
        delete[] data;
        data = new_data;
        capacity = new_cap;
    }
    data[size++] = value;
}

template <typename T>
T* SimpleVector<T>::begin() {
    return data;
}

template <typename T>
T* SimpleVector<T>::end() {
    return data + size;
}

//методы const begin() и const end()
template<typename T>
const T* SimpleVector<T>::begin() const {
    return data;
}
template<typename T>
const T* SimpleVector<T>::end() const {
    return data + size;
}

//реализуем оператор присвавания
template<typename T>
void SimpleVector<T>::operator=(const SimpleVector& other) {
    delete[] data;
    SimpleVector<T> tmp(other);
    data = new T[other.data];
    size = other.size;
    capacity = other.capacity;
    copy(other.begin(), other.end(), begin());
}

//реализуем консруктор перемещения
template<typename T>
SimpleVector<T>::SimpleVector(SimpleVector<T>&& other)
//выделим новую память, под новый обьект
//пронициализировать остальные поля
    : data(other.data)
    , size(other.size)
    , capacity(other.capacity)
{
    //забирам данные у источника
    other.data = nullptr;
    other.size = other.capacity = 0;
}

//реализуем оператор перемещающего присвавания
template<typename T>
void SimpleVector<T>::operator=(SimpleVector&& other) {
    data = other.data;
    size = other.size;
    capacity = other.capacity;
    //освободим other от владения его данными
    other.data = nullptr;
    other.size = other.capacity = 0;
}


int main() {
  //конструктор перемещения
  {
    SimpleVector<int> source(1);
    SimpleVector<int> target = move(source);
    cout << source.Size() << " " << target.Size() << endl;
  }
  
  //оператор перемещающего присваивания
  {
    SimpleVector<int> source(1);
    SimpleVector<int> target(1);
    target = move(source);
    cout << source.Size() << " " << target.Size() << endl;
  }
  /*
    //Что такое rvalue-ссылка?
    target = source;            //вызывается operator=(const vector<int>&)
    target = vector<int>(5);    //вызывается operator=(vector<int>&&)
    target = move(source);      //вызывается operator=(vector<int>&&)
  */

  return 0;
}