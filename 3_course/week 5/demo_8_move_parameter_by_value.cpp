#include <map>
#include <string>

class Person {
public:
/*void ChangeFirstName(int year, const string& first_name) {
//копирование параметра функции в нутрь словоря
first_names[year] = first_name;*/

//примем параметр функции по значению
//call for temporary: move -> move
//else: copy -> move
void ChangeFirstName(int year, string first_name) {
//а здесь уже перемещаем внутрь словаря
first_names[year] = move(first_name);
};

int main() {
	Person person;
	person.ChangeFirstName(2018, string(5));
	return 0;
}