//
// Created by Denis on 15.05.2024.
//

#include "router.hpp"

#include <iostream>
#include <ranges>
#include <styles.hpp>

namespace Navigation {
    using namespace std;

    void hello_screen() {
        const string name = "Ж/Д станция города Н";
        cout << endl;
        cout << Styles::pLogo() << endl;
        cout << endl << endl;

        Styles::bPrintH(name);

        cout << "1) Просмотреть зарезервированные билеты" << endl;
        cout << "2) Зарезервировать билет" << endl;
        cout << "3) Просмотреть все билеты" << endl;
        cout << "4) Об авторе" << endl;
        cout << "5) Выход" << endl;
        cout << endl;
        cout << "Выберите действие: ";
        
    }

    static bool exitToMainMenu = false;
    void show(const vector<NavPoint> &points) {
        int userSelect;
        while (!exitToMainMenu) {
            hello_screen();
            cin >> userSelect;
            if (auto findRoute = ranges::find_if(points, [userSelect](const NavPoint &p) {
                return p.id == userSelect;
            }); findRoute != points.end()) {
                system("cls");
                exitToMainMenu = findRoute->nav();
                }
            if (exitToMainMenu) {
                system("cls");
                exitToMainMenu = false;
            }
        }
    }

};