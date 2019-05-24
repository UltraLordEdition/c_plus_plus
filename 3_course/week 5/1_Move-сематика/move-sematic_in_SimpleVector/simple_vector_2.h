#include <cstdint>
#include <algorithm>
#include <utility>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size);
  //удалим конструктор копирования
  SimpleVector(const SimpleVector& other) = delete;
  //конструктор перемещения
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
  void PushBack(T&& value);

  // При необходимости перегрузите
  // существующие публичные методы

private:
  // Добавьте сюда поля
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

//параметрический конструктор
template<typename T>
SimpleVector<T>::SimpleVector(size_t size)
    : data(new T[size])
    , size(size)
    , capacity(size) {
}
//конструктор перемещения
template<typename T>
SimpleVector<T>::SimpleVector(SimpleVector&& other)
    //выделим новую память, под новый обьект
    : data(other.data)
    , size(other.size)
    , capacity(other.capacity) {
    //забираем данные у источника)
    other.data = nullptr;
    other.size = other.capacity = 0;
}
//деструктор
template<typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] data;
}
//operator[]
template<typename T>
T& SimpleVector<T>::operator[](size_t index) {
    return data[index];
}
//метод begin(), end() и const begin(), const end()
template<typename T>
T* SimpleVector<T>::begin() {
    return data;
}
template<typename T>
const T* SimpleVector<T>::begin() const {
    return data;
}
template<typename T>
T* SimpleVector<T>::end() {
    return data + size;
}
template<typename T>
const T* SimpleVector<T>::end() const {
    return data + size;
}
//метод Size()
template<typename T>
size_t SimpleVector<T>::Size() const {
    return size;
}
//метод Capacity()
template<typename T>
size_t SimpleVector<T>::Capacity() const {
    return capacity;
}
//метод PushBack()
template<typename T>
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
//метод перемещающий PushBack()
template<typename T>
void SimpleVector<T>::PushBack(T&& value) {
    if (size >= capacity) {
        auto new_cap = capacity == 0 ? 1 : 2 * capacity;
        auto new_data = new T[new_cap];
        move(begin(), end(), new_data);
        delete[] data;
        data = new_data;
        capacity = new_cap;
    }
    data[size++] = move(value);
}