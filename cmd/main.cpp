#include "utils.hpp"
#include "router.hpp"
#include <iostream>
#include <conio.h>

using namespace std;

bool helloScreen() {
    cout << "Hello world" << endl;
    _getch();
    return true;
}

auto main () -> int {
    Navigation::NavPoint hScreen {0, helloScreen};
    vector<Navigation::NavPoint> screens;
    screens.push_back(hScreen);
    Navigation::show(screens);
}