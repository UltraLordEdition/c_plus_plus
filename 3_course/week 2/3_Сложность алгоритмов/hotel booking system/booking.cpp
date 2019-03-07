#include "test_runner.h"
#include "profile.h"

#include <iostream>
#include <string>
#include <queue>
#include <cstdint>
#include <map>

using namespace std;

struct BookInfo {
    int64_t time;
    string hotel_name;
    uint32_t client_id;
    uint32_t room_count;
};

class Booking
{
public:
    Booking() {
    }

    void doBooking(const int64_t& time, const string& hotel_name, const uint32_t& client_id, const uint32_t& room_count) {
        Adjust(time);
        BookInfo b;
        b.time = time;
        b.hotel_name = hotel_name;
        b.client_id = client_id;
        b.room_count = room_count;
        events_.push(b);
        //суммируем количество клиентов, которые бронировали комнаты
        clients_[hotel_name][client_id] += client_id;
        //суммируем количество забронированных комнат в отеле
        rooms_[hotel_name] += room_count;
    }

    int getClients(const string& hotel_name) const {
        if (clients_.count(hotel_name) == 0) {
            return 0;
        }
        else {
            return clients_.at(hotel_name).size();
        }
    }

    int getRooms(const string& hotel_name) const {
        if (rooms_.count(hotel_name) == 0) {
            return 0;
        }
        else {
            return rooms_.at(hotel_name);
        }
    }

private:
    //Принимаем новые временные метки и удаляем старые
    void Adjust(int64_t current_time) {
        while (!events_.empty() && (events_.front().time <= current_time - 86400)) {
           //Удаляем комнаты
           rooms_[events_.front().hotel_name] -= events_.front().room_count;
           //если комнат 0 удаляем запись об отеле из базы
           if (rooms_[events_.front().hotel_name] == 0) {
               rooms_.erase(events_.front().hotel_name);
           }
		   //Удаляем клиентов
           clients_[events_.front().hotel_name][events_.front().client_id] -= events_.front().client_id;
           //если клиентов 0б удаляем запись об отеле из базы
           if (clients_[events_.front().hotel_name][events_.front().client_id] == 0) {
               clients_.erase(events_.front().hotel_name);
           }
           events_.pop();
       }
    }
    map<string, int> rooms_;
    map<string, map<int, int>> clients_;
    queue<BookInfo> events_;
};

void TestgetClients() {
    {
        Booking b;
        b.doBooking(0, "FourSeasons", 1, 5);
        ASSERT_EQUAL(b.getClients("FourSeasons"), 1);

        b.doBooking(0, "Marriott", 1, 3);
        ASSERT_EQUAL(b.getClients("Marriott"), 1);

        b.doBooking(86399, "FourSeasons", 1, 2);
        ASSERT_EQUAL(b.getClients("FourSeasons"), 1);

        b.doBooking(86399, "FourSeasons", 2, 2);
        ASSERT_EQUAL(b.getClients("FourSeasons"), 2);
        ASSERT_EQUAL(b.getClients("Marriott"), 1);
        //ровно за сутки
        b.doBooking(86400, "FourSeasons", 2, 3);
        ASSERT_EQUAL(b.getClients("FourSeasons"), 2);
        ASSERT_EQUAL(b.getClients("Marriott"), 0);

        b.doBooking(86410, "FourSeasons", 2, 3);
        ASSERT_EQUAL(b.getClients("FourSeasons"), 2);
        ASSERT_EQUAL(b.getClients("Marriott"), 0);
    }
    {
        Booking b;
        ASSERT_EQUAL(b.getClients("Marriott"), 0);
        b.doBooking(10, "FourSeasons", 1, 2);
        b.doBooking(10, "Marriott", 1, 1);
        b.doBooking(86409, "FourSeasons", 2, 1);
        ASSERT_EQUAL(b.getClients("FourSeasons"), 2);
        ASSERT_EQUAL(b.getClients("Marriott"), 1);
    }
}

void TestgetRooms() {
    {
        Booking b;
        b.doBooking(0, "FourSeasons", 1, 5);
        ASSERT_EQUAL(b.getRooms("FourSeasons"), 5);

        b.doBooking(0, "Marriott", 1, 3);
        ASSERT_EQUAL(b.getRooms("Marriott"), 3);

        b.doBooking(86399, "FourSeasons", 1, 2);
        ASSERT_EQUAL(b.getRooms("FourSeasons"), 7);

        b.doBooking(86399, "FourSeasons", 2, 2);
        ASSERT_EQUAL(b.getRooms("FourSeasons"), 9);
        ASSERT_EQUAL(b.getRooms("Marriott"), 3);
        //ровно за сутки
        b.doBooking(86400, "FourSeasons", 2, 3);
        ASSERT_EQUAL(b.getRooms("FourSeasons"), 7);
        ASSERT_EQUAL(b.getRooms("Marriott"), 0);

        b.doBooking(86410, "FourSeasons", 2, 3);
        ASSERT_EQUAL(b.getRooms("FourSeasons"), 10);
        ASSERT_EQUAL(b.getRooms("Marriott"), 0);
    }
    {
        Booking b;
        ASSERT_EQUAL(b.getRooms("Marriott"), 0);
        b.doBooking(10, "FourSeasons", 1, 2);
        ASSERT_EQUAL(b.getRooms("Hilton"), 0);
        b.doBooking(10, "Marriott", 1, 1);
        ASSERT_EQUAL(b.getRooms("Hilton"), 0);
        b.doBooking(86409, "FourSeasons", 2, 1);
        ASSERT_EQUAL(b.getRooms("Hilton"), 0);
        ASSERT_EQUAL(b.getRooms("FourSeasons"), 3);
        b.doBooking(86410, "Marriott", 2, 10);
        ASSERT_EQUAL(b.getRooms("FourSeasons"), 1);
        ASSERT_EQUAL(b.getRooms("Marriott"), 10);
    }
}

void TestTotal() {
    Booking b;
    ASSERT_EQUAL(b.getClients("Marriott"), 0);
    ASSERT_EQUAL(b.getRooms("Marriott"),0);
    b.doBooking(10, "FourSeasons", 1, 2);
    b.doBooking(10, "Marriott", 1, 1);
    b.doBooking(86409, "FourSeasons", 2, 1);
    ASSERT_EQUAL(b.getClients("FourSeasons"), 2);
    ASSERT_EQUAL(b.getRooms("FourSeasons"),3);
    ASSERT_EQUAL(b.getClients("Marriott"),1);
    b.doBooking(86410, "Marriott", 2, 10);
    ASSERT_EQUAL(b.getRooms("FourSeasons"),1);
    ASSERT_EQUAL(b.getRooms("Marriott"), 10);
}


void TestAll() {
    TestRunner tr;
    RUN_TEST(tr, TestgetClients);
    RUN_TEST(tr, TestgetRooms);
    RUN_TEST(tr, TestTotal);
}

int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    TestAll();

    Booking b;
    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            uint32_t client_id, room_count;
            string hotel_name;
            cin >> time >> hotel_name >> client_id >> room_count;
            b.doBooking(time, hotel_name, client_id, room_count);
        }
        else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << b.getClients(hotel_name) << "\n";
        }
        else if (query_type == "ROOMS")
        {
            string hotel_name;
            cin >> hotel_name;
            cout << b.getRooms(hotel_name) << "\n";
        }
    }

    return 0;
}