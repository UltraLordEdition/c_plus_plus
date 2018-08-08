#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {
	/* ƒл€ тестировани€ повставл€йте сюда код, реализующий различное поведение этой функии:
	* нормальный возврат строкового значени€
	* выброс исключени€ system_error
	* выброс другого исключени€ с сообщением.
	*/
	//return "00:00:01";
	//throw system_error(error_code());
	//throw invalid_argument("Invalid argument");
}

class TimeServer {
public:
	string GetCurrentTime() {
		/* –еализуйте этот метод:
		* если AskTimeServer() вернула значение, запишите его в LastFetchedTime и верните
		* если AskTimeServer() бросила исключение system_error, верните текущее значение
		пол€ LastFetchedTime
		* если AskTimeServer() бросила другое исключение, пробросьте его дальше.
		*/
		try {
			LastFetchedTime = AskTimeServer();
		}catch (const system_error& x)
		{
			return LastFetchedTime;
		}

		return LastFetchedTime;
	}

private:
	string LastFetchedTime = "00:00:00";
};

int main() {
	// ћен€€ реализацию функции AskTimeServer, убедитесь, что это код работает корректно
	TimeServer ts;
	try {
		cout << ts.GetCurrentTime() << endl;
	}
	catch (exception& e) {
		cout << "Exception got: " << e.what() << endl;
	}
	return 0;
}
