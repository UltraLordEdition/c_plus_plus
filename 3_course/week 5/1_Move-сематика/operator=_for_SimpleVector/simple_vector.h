#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    //конструктор от размера
    explicit SimpleVector(size_t size);
    //конструктор копирования
    SimpleVector(const SimpleVector& other);
    ~SimpleVector();

    T& operator[](size_t index);

    T* begin();
    T* end();

    const T* begin() const;
    const T* end() const;
    
    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);

    //добвам оператор присваивания
    void operator=(const SimpleVector& other);

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

//реализуем оператор присваивания
template<typename T>
void SimpleVector<T>::operator=(const SimpleVector& other) {
    SimpleVector<T> tmp(other);    
    if (tmp.size <= capacity) {
        // У нас достаточно памяти - просто копируем элементы
        copy(tmp.begin(), tmp.end(), begin());
        size = tmp.size;
    }
    else {
        // Это так называемая идиома copy-and-swap.
        // Мы создаём временный вектор с помощью
        // конструктора копирования, а затем обмениваем его поля со своими.
        // Так мы достигаем двух целей:
        //  - избегаем дублирования кода в конструкторе копирования
        //    и операторе присваивания
        //  - обеспечиваем согласованное поведение конструктора копирования
        //    и оператора присваивания
        swap(tmp.data, data);
        swap(tmp.size, size);
        swap(tmp.capacity, capacity);
    }
}