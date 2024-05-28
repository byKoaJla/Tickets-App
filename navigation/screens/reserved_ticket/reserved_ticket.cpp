//
// Created by Denis on 17.05.2024.
//

#include "reserved_ticket.hpp"

#include <conio.h>
#include <iostream>

#include "styles.hpp"
#include "database.hpp"
#include "ticket.hpp"
#include "reservedTicket.hpp"
#include "appconf.h"

namespace Reserved_Ticket {
    using namespace std;

    int limit_path = SHOW_LIMIT;
    string ticket_path = MOCK_TICKET_PATH;
    string reserved_ticket_path = RESERVED_TICKET_PATH;

    auto searchTickets(const std::list<Ticket> &tickets,
                        std::string day,
                        const std::string &time,
                        const std::string &destination,
                        const int seats) -> std::list<Ticket>
    {
        day.erase(1,1);
        std::list<Ticket> result;
        for (const auto &t : tickets) {
            auto _tR = Utils::rusUp2Down(t.ticket.getDestination());
            if (auto _tO = Utils::rusUp2Down(destination);
                t.ticket.getDay() == day &&
                Utils::timeToSeconds(t.ticket.getTime()) <= Utils::timeToSeconds(time) &&
                _tR == _tO &&
                t.ticket.getSeats() >= seats) {
                result.push_back(t);
                }
        }
        return result;
    }

    void displayList(list<Ticket>& datalist, const int limit, const int& currentPosition) {
        const auto start = next(datalist.begin(), currentPosition);
        const auto end = next(start, limit);
        Styles::ticket_header();
        for (auto it = start; it != end && it != datalist.end(); ++it) {
            Ticket::bPrint(*it);
        }
        std::cout << std::endl;
        std::cout << datalist.size() << " (записей) / " << (currentPosition + limit) << " (открыто)" << std::endl;
        Styles::user_interface("(r) [Зарерервировать] (q) [Выход]:\t");
    }

    void reserveTicket(Db::Store<Ticket>& mDb) {
        std::string id, phone;
        int nSeats;
        std::cout << "Введите ID билета, кол-во мест и номер телефона:\n>> ";
        std::cin >> id >> nSeats >> phone;

        Db::Store<ReservedTicket> rStore(reserved_ticket_path);
        if (Ticket t = mDb.getItemByID(id); t.ticket.getSeats() > nSeats) {
            ReservedTicket rt(id, {t.ticket.getDay(), t.ticket.getTime(), t.ticket.getDestination(), nSeats}, phone);
            REPEAT:
            int confirm;
            cout << "Зарерервировать?([0] Да | [1] Нет): ";
            cin >> confirm;
            if (cin.fail()) {
                cout << "Нет такого варианта!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                goto REPEAT;
            } else if(confirm == 1) {
                return;
            } else {
                cout << "Места зарезервированы."<<endl;
                rStore.save(rt);
                _getch();
            }
            t.ticket.setSeats(t.ticket.getSeats() - nSeats);
            auto updTicket = t;
            mDb.updateItemByID(id, updTicket);
        } else {
            std::cout << "Недостаточно свободных мест для бронирования.\n";
        }
    }
    bool returnToMenu = false;

    bool reserved_ticket_view() {
        while (!returnToMenu) {
            system("cls");
            string title = "Резервирование билета";
            Styles::bPrintH(title);
            Db::Store<Ticket> fullTickets(ticket_path);
            auto tickets = Ticket::liquidItems(fullTickets.loadAll());

            std::string day, time, destination;
            int seats;
            std::cout << "Введите параметры для поиска:\n"
                      << "День (пн, вт и т.д.), Время (10:00), Направление (Минск), Кол-во мест (5) | (q) для выхода \n"
                      << ">> ";
            std::cin >> day;

            if (day == "q") {
                std::cout << "Выход из программы...\n";
                break;
            }
            std::cin >> time >> destination >> seats;
            auto foundTickets = searchTickets(tickets, Utils::getDayOfWeek(day), time, destination, seats);

            std::cout << "\nНайденные билеты:\n";
            if (foundTickets.empty()) {
                std::cout << "Билеты по заданным параметрам не найдены\n";
                _getch();
            } else {
                char uInput;
                int currentPossition = 0;
                displayList(foundTickets, foundTickets.size(), currentPossition);

                cin >> uInput;
                if (uInput == 'r') {
                    reserveTicket(fullTickets);
                } else if (uInput == 'q') {
                   returnToMenu = true;
                }
            }
        }
        return returnToMenu;
    }
    bool reserved_ticket_screen() {
        return reserved_ticket_view();
    }

} // All_Tickets