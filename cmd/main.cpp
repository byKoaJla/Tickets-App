#include <database.hpp>
#include <iostream>
#include <locale>
#include <ticket.hpp>

#include "router.hpp"
#include "routes.hpp"
#include "appconf.h"
using namespace std;



auto main () -> int {
    Db::Store<Ticket> mockTickets(MOCK_TICKET_PATH);
    Ticket t1 {Ticket::ObjectID(), Db::S_ticket{"2024-05-20", "10:00", "Минск", 10}};
    mockTickets.save(t1);
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());
    const auto points = Routes::screens_graph();
    Navigation::show(points);
}