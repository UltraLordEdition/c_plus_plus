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
    }

    ~SimpleVector() {
        //��������� ������! (����� ������ ������)
        delete[] data;
    }

private:
    T* data;
};

int main() {
    SimpleVector<int> sv(5);
}