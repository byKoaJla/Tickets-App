//
// Created by Denis on 15.05.2024.
//


#include "styles.hpp"

#include <iomanip>
#include <string>
#include <iostream>
#include <utils.hpp>

using namespace std;
namespace Styles {
    void bPrintH( const string &str) {
        cout << endl;
        cout << "+" << setfill('-')<< setw(Utils::strlen(str)+3) << "+" << endl;
        cout << "| " << str << " |" << endl;
        cout << "+" << setfill('-')<< setw(Utils::strlen(str)+3) << "+" << endl;
        cout << endl;
    }

    void user_interface(const string &n_line) {
        cout << endl;
        cout << n_line;
    }

    void ticket_header() {
        cout << left << setfill(' ') << setw(15) << "Номер"
                  << setw(17) << "День"
                  << setw(14) << "Время"
                  << setw(29) << "Направление"
                  << right << setw(20) << "Свободные места" << endl;
        cout << string(66, '-') << endl;
    }
    void reseved_header() {
        cout << left << setfill(' ') << setw(15) << "Номер"
                  << setw(16) << "День"
                  << setw(15) << "Время"
                  << setw(30) << "Направление"
                  << setw(20) << "Зарезерв. места"
                  << right << setw(30) << "Номер телефона"<< endl;
        cout << string(85, '-') << endl;
    }

    string pLogo() {
        const string logo =
        "    /$$$$$$  /$$   /$$                      /$$   /$$\n"
        "   /$$__  $$|__/  | $$                     | $$$ | $$\n"
        "   | $$  \\__/ /$$ /$$$$$$   /$$   /$$      | $$$$| $$\n"
        "   | $$      | $$|_  $$_/  | $$  | $$      | $$ $$ $$\n"
        "   | $$      | $$  | $$    | $$  | $$      | $$  $$$$\n"
        "   | $$    $$| $$  | $$ /$$| $$  | $$      | $$\\  $$$\n"
        "   |  $$$$$$/| $$  |  $$$$/|  $$$$$$$      | $$ \\  $$\n"
        "    \\______/ |__/   \\___/   \\____  $$      |__/  \\__/\n"
        "                            /$$  | $$                \n"
        "                           |  $$$$$$/                \n"
        "                           \\______/                  \n";

        return logo;
    }
}