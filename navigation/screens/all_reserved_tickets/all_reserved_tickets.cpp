//
// Created by Denis on 17.05.2024.
//

#include "all_reserved_tickets.hpp"

#include <conio.h>
#include <iostream>
#include <list>
#include <string>
#include <styles.hpp>

#include "reservedTicket.hpp"

#include "appconf.h"

namespace All_Reserved_Tickets {
    using namespace std;

    string reserveted_tickets_path = RESERVED_TICKET_PATH;
    int limit_path = SHOW_LIMIT;

    void displayList(list<ReservedTicket>& datalist, const int limit, const int& currentPosition) {
        const auto start = next(datalist.begin(), currentPosition);
        const auto end = next(start, limit);
        Styles::reseved_header();
        for (auto it = start; it != end && it != datalist.end(); ++it) {
            ReservedTicket::bPrint(*it);
        }
        cout << std::endl;
        cout << datalist.size() << " (записей) / " << (currentPosition + limit) << " (открыто)" << endl;
        Styles::user_interface("(4) [перейти назад] (6) [перейти вперед] (s) [Сортировать по..] (f) [поиск по номеру] (d) удалить резерв (q) [Выход]:\t");
    }

    void sortTickets(std::list<ReservedTicket>& tickets, const int choice) {
        switch (choice) {
            case 0: // По дате
                tickets.sort([](ReservedTicket& a, ReservedTicket& b) {
                  return ReservedTicket::eq(a, b, 0);
              });
            break;
            case 1: // По времени
                tickets.sort([](ReservedTicket& a, ReservedTicket& b) {
                    return ReservedTicket::eq(a, b, 1);
                });
            break;
            case 2: // По направлению
                tickets.sort([](ReservedTicket& a, ReservedTicket& b) {
                   return ReservedTicket::eq(a, b, 2);
               });
            break;
            case 3: // По свободным местам
                tickets.sort([](ReservedTicket& a, ReservedTicket& b) {
                   return ReservedTicket::eq(a, b, 3);
               });
            break;
            default:
                std::cout << "Некорректный выбор сортировки." << std::endl;
            break;
        }
    }

    void filterTickets(list<ReservedTicket>& tickets) {
        string phone;
        cout << "Введите телефон для поиска: ";
        cin >> phone;
        const list<ReservedTicket> oldTickets = tickets;
        tickets.remove_if([&](const ReservedTicket& ticket) {
            return ticket.getPhone() != phone;
        });
        if (tickets.empty()) {
            cout << "Не найдено резерва с таким номером" << endl;
            tickets = oldTickets;
            _getch();
        }
    }

    void removeTicket(Db::Store<ReservedTicket> &rt, list<ReservedTicket> &lrt) {
        cout << "Введите НОМЕР резерва чтобы удалить его: ";
        string removeItem;
        cin >> removeItem;
        REPEAT:
        int confirm;
        cout << "Удалить #" << removeItem << ". [(0) Да | (1) Нет]: ";
        cin >> confirm;
        if (cin.fail()) {
            cout << "Нет такого варианта!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto REPEAT;
        } else if(confirm == 1) {
            return;
        } else {
            cout << "Резерв #" << removeItem << "удален."<<endl;
            rt.removeItemByID(removeItem);
            lrt.remove_if([&](const ReservedTicket &t) {
                return t.getID() == removeItem;
            });
            _getch();
        }

    }

    bool allReservedTicketsView() {
        const auto title = "Просмотр всех зарезервированных билетов";
        Styles::bPrintH(title);
        Db::Store<ReservedTicket> reservedStore(reserveted_tickets_path);
        int currentPosition = 0;
        int limit = limit_path;
        list<ReservedTicket> lqTickets = ReservedTicket::liquidItems(reservedStore.loadAll());
        cout << std::endl;
        if (lqTickets.size() < limit) { limit = static_cast<int>(lqTickets.size()); }
        displayList(lqTickets, limit, currentPosition);
        char input;
        while (std::cin >> input) {
            if (input == '4') {
                currentPosition = std::max(0, currentPosition - limit);
            } else if (input == '6') {
                currentPosition = std::min(static_cast<int>(lqTickets.size()) - limit, currentPosition + limit);
            } else if (input == 's') {
                std::cout << std::endl;
                std::cout << "Выберите поле для сортировке (0) [по дате] (1) [по времени] (2) [по направлению] (3) [по свободным местам]: ";
                int choice;
                std::cin >> choice;
                sortTickets(lqTickets, choice);
            } else if (input == 'f') {
                filterTickets(lqTickets);
            }else if (input == 'd') {
                removeTicket(reservedStore, lqTickets);
            }
            system("cls");
            Styles::bPrintH(title);
            if (lqTickets.size() < limit) { limit = static_cast<int>(lqTickets.size()); }
            displayList(lqTickets, limit, currentPosition);
            if (input == 'q') {
                return true;
            }
        }
        return false;
    }

    bool allReservedTicketsScreen() {
        return allReservedTicketsView();
    }

}
