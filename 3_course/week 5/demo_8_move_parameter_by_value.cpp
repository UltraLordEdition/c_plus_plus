#include <map>
#include <string>

class Person {
public:
/*void ChangeFirstName(int year, const string& first_name) {
//����������� ��������� ������� � ����� �������
first_names[year] = first_name;*/

//������ �������� ������� �� ��������
//call for temporary: move -> move
//else: copy -> move
void ChangeFirstName(int year, string first_name) {
//� ����� ��� ���������� ������ �������
first_names[year] = move(first_name);
};

int main() {
	Person person;
	person.ChangeFirstName(2018, string(5));
	return 0;
}