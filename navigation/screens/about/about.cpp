//
// Created by Denis on 16.05.2024.
//

#include "about.hpp"
#include "styles.hpp"
#include <string>
#include <iostream>
#include <conio.h>

namespace About {
    using namespace std;
    void about_view() {
        const string title = "Об авторе";
        const string content = "Моя первая курсовая работа - "
                       "консольное приложение на C++, "
                       "бронирующее билеты на определенное "
                       "число людей на конкретную дату. Для "
                       "подробностей обращайтесь на "
                       "GitHub: https://github.com/byKoT3uJla/Tickets-App/";


        Styles::bPrintH(title);
        cout << endl;
        cout << content << endl;
    };
    bool about_screen() {
        about_view();
        _getch();
        return true;
    };
}
