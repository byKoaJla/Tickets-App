#include <iostream>
#include <locale>

#include "router.hpp"
#include "routes.hpp"

using namespace std;



auto main () -> int {
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    const auto points = Routes::screens_graph();
    Navigation::show(points);
}