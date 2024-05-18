#include <database.hpp>
#include <iostream>
#include <locale>
#include <mock.hpp>
#include <ticket.hpp>

#include "router.hpp"
#include "routes.hpp"
#include "appconf.h"
using namespace std;



auto main () -> int {
    MockTickets::generate(10);
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());
    const auto points = Routes::screens_graph();
    Navigation::show(points);
}