#include <iostream>
#include <vector>
#include <future>
#include <numeric>

using namespace std;

// Обычная однопоточная программа
/*
int SumToVectors(const vector<int>& one, const vector<int>& two) {
    return accumulate(begin(one), end(one), 0)
        + accumulate(begin(two), end(two), 0);
}

int main() {
    cout << SumToVectors({ 1,1,1,1 }, { 3,3,3 });
}
*/

int SumToVectors(const vector<int>& one, const vector<int>& two) {
    //запускаем асинхронную операцию
    //int потому что лямбда функция возвращает тип int
    //[one] - копирование; [&one] - захват по ссылке
    future<int> f = async([&one] {
        return accumulate(begin(one), end(one), 0);
    });
    int result = accumulate(begin(two), end(two), 0);
    return result + f.get();
}

int main() {
    cout << SumToVectors({ 1,1,1,1 }, { 3,3,3 });
}