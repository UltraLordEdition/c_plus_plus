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
    size_t capacity_;
    size_t size_;
};

//конструктор по умолчанию
template <typename T>
SimpleVector<T>::SimpleVector() {
    data = nullptr;
    end_ = data;
    size_ = 0;
    capacity_ = 0;
}

//параметрический конструктор
template <typename T>
SimpleVector<T>::SimpleVector(size_t size) {
    data = new T[size];
    end_ = data + size;
    size_ = size;
    capacity_ = size;
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
    return size_;
}

//метод capacity()
template <typename T>
size_t SimpleVector<T>::Capacity() const {
    return capacity_;
}

//метод push_back()
template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
    if (SimpleVector<T>::Size() == SimpleVector<T>::Capacity()) {
        T* data_new = nullptr;
        T* begin = nullptr;

        if (SimpleVector<T>::Capacity() == 0u) {
            data_new = new T[1];
            begin = data_new;
            capacity_ = 1u;
        }
        else if (SimpleVector<T>::Capacity() > 0u) {
            data_new = new T[2u * SimpleVector<T>::Capacity()];
            begin = data_new;
            capacity_ = 2u * SimpleVector<T>::Capacity();
        }

        for (T* i = data; i != end_; i++) {
           *data_new = *i;
           data_new++;
        }
        delete[] data;
        data = begin;
        end_ = data_new;
    }
    *(data + size_) = value;
    size_++;
    end_++;
}