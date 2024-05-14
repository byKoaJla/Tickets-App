#include "utils.hpp"
#include <iostream>

auto main () -> int {
    auto str = "Привет мир";
    std::cout << Utils::rusUp2Down(str) << std::endl;
}