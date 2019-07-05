#include "profile.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <future>
#include <functional>
#include <mutex>
using namespace std;

struct Account {
    int balance = 0;
    // добавим вектор историй
    vector<int> history;
    //добавим mutex
    mutex m;

    bool Spend(int value) {
    	// найдем критическую секцию и защитим ее мьютексом
    	// выполняем синхронизацию потоков
    	lock_guard<mutex> g(m);
    	// здесь мы захватываем мьютекс в конструкторе класса lock_guard<mutex>
    	// а совобождаем в деструкторе
    	//lock_guard g(m); - так тоже можно писать (в шаблоне класса есть конструктор)
    	if (value <= balance) {
            balance -= value;
            //добавляем историю
            history.push_back(value);
            return true;
        }
        return false;
    }
};

int SpendMoney(Account& account) {
    int total_spent = 0;
    for (int i = 0; i < 100000; ++i) {
        if (account.Spend(1)) {
            ++total_spent;
        }
    }
    return total_spent;
}

int main() {
    Account family_account{ 100000 };

    // семья из 4 чловек, параллельно тратит деньги
    auto husband = async(SpendMoney, ref(family_account));
    auto wife = async(SpendMoney, ref(family_account));
    auto son = async(SpendMoney, ref(family_account));
    auto daughter = async(SpendMoney, ref(family_account));

    // сколько они тратят
    int spent = husband.get() + wife.get() + son.get() + daughter.get();

    // если несколько потоков обращаются к одной и той же переменной,
    // целостность данных может быть нарушена
    // как в примере выше
    // для ее сохранения необходимо выполнять синхронизацию

    cout << "Total spent: " << spent << endl
        << "Balance: " << family_account.balance << endl;
}
