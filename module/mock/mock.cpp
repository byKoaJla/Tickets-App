//
// Created by Denis on 18.05.2024.
//

#include "mock.hpp"

#include <ctime>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include "ticket.hpp"
#include "database.hpp"

#include "appconf.h"

namespace MockTickets {
    using namespace std;

    string mock_ticket_path = MOCK_TICKET_PATH;

    string getRandomDateOnCurrentWeek()
    {
        time_t now = time(nullptr);
        tm* localTime = localtime(&now);
        int dayOfWeek = localTime->tm_wday;
        now -= static_cast<long long>(dayOfWeek) * 24 * 60 * 60;
        localTime = localtime(&now);

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 6);

        int randomDay = dis(gen);
        now += static_cast<long long>(randomDay) * 24 * 60 * 60;
        localTime = localtime(&now);

        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
        return string(buffer);
    }

    string randomCity()
    {
        const vector<string> cities{
            "Минск",
            "Витебск",
            "Полоцк",
            "Гродно",
            "Могилев",
            "Жодино",
            "Брест",
            "Городок",
            "Вилейка",
            "Мир",
            "Браслов"
        };
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, cities.size() - 1);

        int randomIndex = dis(gen);
        return cities[randomIndex];
    }

    string randomTime()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> disHour(0, 23); // Генерация случайного числа для часов (от 0 до 23)
        uniform_int_distribution<> disMinute(0, 59); // Генерация случайного числа для минут (от 0 до 59)

        const int randomHour = disHour(gen);
        const int randomMinute = disMinute(gen);
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << randomHour << ":"
           << std::setw(2) << std::setfill('0') << randomMinute;
        return ss.str();
    }

    void generate(int limit) {
        Db::Store<Ticket> mockStore(mock_ticket_path);
        for (int c = 0; c <= limit; c++) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, 100);
            const int randomSeats = dis(gen);

            Ticket _ticket {Db::Atom::ObjectID(), {
                getRandomDateOnCurrentWeek(),
                randomTime(),
                randomCity(),
                randomSeats,
            }};
            mockStore.save(_ticket);
        }
    }

}
