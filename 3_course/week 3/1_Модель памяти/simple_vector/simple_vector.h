#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector();
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  T& operator[](size_t index);
  
  T* begin();
  T* end();

  const T* begin() const;
  const T* end() const;
  
  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

private:
  // Добавьте поля для хранения данных вектора
    T* data;
    T* end_;
    size_t index_;
};

//конструктор по умолчанию
template <typename T>
SimpleVector<T>::SimpleVector() {
    data = new T(0);
    end_ = data;
    index_ = 0;
}

//параметрический конструктор
template <typename T>
SimpleVector<T>::SimpleVector(size_t size) {
    data = new T[size];
    end_ = data + size;
    index_ = 0;
}

//деструктор освобождает память
template<typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] data;
}

//operator[]
template<typename T>
T& SimpleVector<T>::operator[](size_t index) {
    return data[index];
}

//методы begin() и end()
template<typename T>
T* SimpleVector<T>::begin() {
    return data;
}
template<typename T>
T* SimpleVector<T>::end() {
    return end_;
}

//методы const begin() и const end()
template<typename T>
const T* SimpleVector<T>::begin() const{
    return data;
}
template<typename T>
const T* SimpleVector<T>::end() const {
    return end_;
}

//метод size()
template <typename T>
size_t SimpleVector<T>::Size() const {
    return end_- data;
}

//метод capacity()
template <typename T>
size_t SimpleVector<T>::Capacity() const {
    return end_-data;
}

//метод push_back()
template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
    /*if (SimpleVector<T>::Size() == SimpleVector<T>::Capacity()) {
        T* data_new = new T[2 * SimpleVector<T>::Capacity()];

    }*/
    data[index_] = value;
    index_++;
    ++end_;
}