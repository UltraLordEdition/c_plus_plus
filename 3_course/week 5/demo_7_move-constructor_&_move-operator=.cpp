#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    //����������� �� �������
    explicit SimpleVector(size_t size);
    //����������� ����������� = ����������� ���� �� �� �������� ����������� �����������
    SimpleVector(const SimpleVector& other);
    //����������� �����������
    //rvalue reference - ��������� ��������� ��������� �������
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

    //�������� ����������� ������������
    void operator=(const SimpleVector& other);

    //�������� ������������� ������������
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

//��������� ����������� �����������
template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T>& other)
//������� ����� ������, ��� ����� ������
//������������������ ��������� ����
    : data(new T[other.capacity])
    , size(other.size)
    , capacity(other.capacity)
{
    //� ��������� ��� ������
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

//������ const begin() � const end()
template<typename T>
const T* SimpleVector<T>::begin() const {
    return data;
}
template<typename T>
const T* SimpleVector<T>::end() const {
    return data + size;
}

//��������� �������� �����������
template<typename T>
void SimpleVector<T>::operator=(const SimpleVector& other) {
    delete[] data;
    SimpleVector<T> tmp(other);
    data = new T[other.data];
    size = other.size;
    capacity = other.capacity;
    copy(other.begin(), other.end(), begin());
}

//��������� ���������� �����������
template<typename T>
SimpleVector<T>::SimpleVector(SimpleVector<T>&& other)
//������� ����� ������, ��� ����� ������
//������������������ ��������� ����
    : data(other.data)
    , size(other.size)
    , capacity(other.capacity)
{
    //������� ������ � ���������
    other.data = nullptr;
    other.size = other.capacity = 0;
}

//��������� �������� ������������� �����������
template<typename T>
void SimpleVector<T>::operator=(SimpleVector&& other) {
    data = other.data;
    size = other.size;
    capacity = other.capacity;
    //��������� other �� �������� ��� �������
    other.data = nullptr;
    other.size = other.capacity = 0;
}


int main() {
  //����������� �����������
  {
    SimpleVector<int> source(1);
    SimpleVector<int> target = move(source);
    cout << source.Size() << " " << target.Size() << endl;
  }
  
  //�������� ������������� ������������
  {
    SimpleVector<int> source(1);
    SimpleVector<int> target(1);
    target = move(source);
    cout << source.Size() << " " << target.Size() << endl;
  }
  /*
    //��� ����� rvalue-������?
    target = source;            //���������� operator=(const vector<int>&)
    target = vector<int>(5);    //���������� operator=(vector<int>&&)
    target = move(source);      //���������� operator=(vector<int>&&)
  */

  return 0;
}