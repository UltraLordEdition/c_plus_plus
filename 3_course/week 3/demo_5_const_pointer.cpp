#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//������ ������
template<typename T>
class SimpleVector {
public:
    explicit SimpleVector(size_t size) {
        //������� � ���� ���� ������ ��� 5 �������
        data = new T[size];
        end_ = data + size;
    }

    ~SimpleVector() {
        //��������� ������! (����� ������ ������)
        delete[] data;
    }

    //������� ����������� ���������� � ��������� ���������
    T& operator[](size_t index) {
        return data[index]; //������������ *(data+index);
    }
    //������� ������ begin � end ��� range based for loop
    //��������� �� ������� ���� �
    //��������� �� �������� ������� ����� ������������ � �������� ��� ����������
    //���������� ��� �� ����������� �������
    T* begin() { return data; }
    T* end() { return end_; }

    //��������� �� ��������� �.� ����� ������� ���������, �� ������ �� �����
    //��� �������� �� ���������� ������� ��� ���������� �����������
    const T* begin() const { return data; }
    const T* end() const { return end_; }

private:
    T* data;
    T* end_;
};

//������� ������ �������
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
    
    //����� ���
    *px = 1;
    ++px;

    //��������� �� ���������
    //*cpx = 1;
    ++cpx;

    //����������� ���������
    *pxc = 1;
    //++pxc;

    //����������� ��������� �� ���������
    //*cpxc = 1;
    //++cpxc;
}