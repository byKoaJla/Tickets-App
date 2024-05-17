#include "all_tickets.hpp"

#include <iostream>

#include "styles.hpp"
#include "ticket.hpp"
#include "database.hpp"
#include "appconf.h"

namespace All_Tickets {
    using namespace std;

    string mock_tickets_path = MOCK_TICKET_PATH;
    int show_limit = SHOW_LIMIT;

    void displayList(list<Ticket>& datalist, const int limit, const int& currentPosition) {
        const auto start = next(datalist.begin(), currentPosition);
        const auto end = next(start, limit);
        Styles::ticket_header();
        for (auto it = start; it != end && it != datalist.end(); ++it) {
            Ticket::bPrint(*it);
        }
        std::cout << std::endl;
        std::cout << datalist.size() << " (записей) / " << (currentPosition + limit) << " (открыто)" << std::endl;
        Styles::user_interface("(4) [перейти назад] (6) [перейти вперед] (s) [Сортировать по..] (f) [Фильтровать] (q) [Выход]:\t");
    }

    void sortTickets(std::list<Ticket>& tickets, const int choice) {
        switch (choice) {
            case 0: // По дате
                tickets.sort([](Ticket& a, Ticket& b) {
                  return Ticket::eq(a, b, 0);
              });
                break;
            case 1: // По времени
                tickets.sort([](Ticket& a, Ticket& b) {
                    return Ticket::eq(a, b, 1);
                });
                break;
            case 2: // По направлению
                tickets.sort([](Ticket& a, Ticket& b) {
                   return Ticket::eq(a, b, 2);
               });
                break;
            case 3: // По свободным местам
                tickets.sort([](Ticket& a, Ticket& b) {
                   return Ticket::eq(a, b, 3);
               });
                break;
            default:
                std::cout << "Некорректный выбор сортировки." << std::endl;
                break;
        }
    }

    void filterTickets(std::list<Ticket>& tickets) {
        string destination;
        cout << "Введите направление для фильтрации: ";
        cin >> destination;
        tickets.remove_if([&](const Ticket& ticket) {
            return ticket.ticket.getDestination() != destination;
        });
    }

    bool all_tickets_view() {
        const auto title = "Просмотр всех билетов";
        Styles::bPrintH(title);
        Db::Store<Ticket> mockStore(mock_tickets_path);
        int currentPosition = 0;
        int limit = show_limit;
        list<Ticket> lqTickets = Ticket::liquidItems(mockStore.loadAll());
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
            }
            system("cls");
            Styles::bPrintH(title);
            if (lqTickets.size() < limit) { limit = static_cast<int>(lqTickets.size()); }
            displayList(lqTickets, limit, currentPosition);
            if (input == 'q') {
                return true;
                break;
            }
        }
        return false;
    }

    bool all_tickets_screen() {
        return all_tickets_view();
    }
} // All_Tickets