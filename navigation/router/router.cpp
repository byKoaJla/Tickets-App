#include "router.hpp"
#include <conio.h>
#include <iostream>
#include <ranges>
#include <styles.hpp>

namespace Navigation {
    using namespace std;

    void printMainMenu() {
        const string stationName = "Ж/Д станция города Н";
        cout << endl << Styles::pLogo() << endl << endl;
        Styles::bPrintH(stationName);
        cout << "1) Просмотреть зарезервированные билеты" << endl;
        cout << "2) Зарезервировать билет" << endl;
        cout << "3) Просмотреть все билеты" << endl;
        cout << "4) Об авторе" << endl;
        cout << "5) Выход" << endl << endl;
        cout << "Выберите действие: ";
    }

    int getUserSelection() {
        int userSelection;
        if (std::isdigit(std::cin.peek())) {
            std::cin >> userSelection;
            return userSelection;
        } else {
            std::cin.clear();
            std::string invalidInput;
            std::getline(std::cin, invalidInput);
            return -1; // Возвращаем некорректное значение для обработки ошибки в вызывающей функции
        }
    }

    static bool exitToMainMenu = false;
    void show(const vector<NavPoint> &points) {
        while (!exitToMainMenu) {
            printMainMenu();
            int userSelection = getUserSelection();
            if (userSelection == -1) {
                cout << "Ошибка: введите число, а не букву." << std::endl;
                system("cls");
                continue; // Пропускаем остаток цикла и снова выводим главное меню
            }
            system("cls");
            auto findRoute = ranges::find_if(points, [userSelection](const NavPoint& point) {
                return point.id == userSelection;
            });
            
            if (findRoute != points.end()) {
                exitToMainMenu = findRoute->nav();
                system("cls");
            } else {
                cout << "Нет такого действия, попробуйте еще раз" << endl;
                cin.ignore();
            }

            if (exitToMainMenu) {
                exitToMainMenu = false;
            }
        }
    }
}
