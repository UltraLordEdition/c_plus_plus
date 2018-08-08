#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {
	/* ��� ������������ ������������ ���� ���, ����������� ��������� ��������� ���� ������:
	* ���������� ������� ���������� ��������
	* ������ ���������� system_error
	* ������ ������� ���������� � ����������.
	*/
	//return "00:00:01";
	//throw system_error(error_code());
	//throw invalid_argument("Invalid argument");
}

class TimeServer {
public:
	string GetCurrentTime() {
		/* ���������� ���� �����:
		* ���� AskTimeServer() ������� ��������, �������� ��� � LastFetchedTime � �������
		* ���� AskTimeServer() ������� ���������� system_error, ������� ������� ��������
		���� LastFetchedTime
		* ���� AskTimeServer() ������� ������ ����������, ���������� ��� ������.
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
	// ����� ���������� ������� AskTimeServer, ���������, ��� ��� ��� �������� ���������
	TimeServer ts;
	try {
		cout << ts.GetCurrentTime() << endl;
	}
	catch (exception& e) {
		cout << "Exception got: " << e.what() << endl;
	}
	return 0;
}
