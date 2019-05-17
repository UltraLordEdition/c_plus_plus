//lvalue reference - для постоянных объектов(копирование)
void push_back(const T& value);
//rvalue reference - для временных объектов (перемещение)
void push_back(T&& value);