#include "utils.hpp"

#include <codecvt>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>
#include <map>
#include <sstream>

using namespace std;
namespace Utils {

    string rusUp2Down(const std::string &str) {
        std::string result;
        std::map<char, char> rus_alphabet = {
            {'А', 'а'}, {'Б', 'б'}, {'В', 'в'}, {'Г', 'г'}, {'Д', 'д'},
            {'Е', 'е'}, {'Ё', 'ё'}, {'Ж', 'ж'}, {'З', 'з'}, {'И', 'и'},
            {'Й', 'й'}, {'К', 'к'}, {'Л', 'л'}, {'М', 'м'}, {'Н', 'н'},
            {'О', 'о'}, {'П', 'п'}, {'Р', 'р'}, {'С', 'с'}, {'Т', 'т'},
            {'У', 'у'}, {'Ф', 'ф'}, {'Х', 'х'}, {'Ц', 'ц'}, {'Ч', 'ч'},
            {'Ш', 'ш'}, {'Щ', 'щ'}, {'Ъ', 'ъ'}, {'Ы', 'ы'}, {'Ь', 'ь'},
            {'Э', 'э'}, {'Ю', 'ю'}, {'Я', 'я'}
        };

        for (const auto &ch : str) {
            bool found = false;
            for (const auto &[fst, snd] : rus_alphabet) {
                if (ch == fst) {
                    result += snd;
                    found = true;
                    break;
                }
            }
            if (!found) {
                result += ch;
            }
        }
    return result;
}

    string getDayOfWeek(const std::string& day) {
    std::map<std::string, int> weekdays = {
        {"пн", 1}, {"вт", 2}, {"ср", 3}, {"чт", 4}, {"пт", 5}, {"сб", 6}, {"вс", 0}
    };

    const time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    const int dayOfWeek = localTime->tm_wday;
    int daysToTarget = weekdays[day] - dayOfWeek;
    if (daysToTarget < 0) {
        daysToTarget += 7;
    }

    localTime->tm_mday += daysToTarget;
    mktime(localTime);

    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << localTime->tm_year + 1900
       << "-" << std::setw(2) << std::setfill('0') << localTime->tm_mon + 1
       << "-" << std::setw(2) << std::setfill('0') << localTime->tm_mday;

    return ss.str();
}

    int timeToSeconds(const std::string &timeStr) {
    int hours, minutes;
    char colon;
    std::stringstream ss(timeStr);
    ss >> hours >> colon >> minutes;
    return hours * 3600 + minutes * 60;
}

    Date parseDate(const std::string& dateStr) {
    int year, month, day;
    char dash1, dash2;
    std::stringstream ss(dateStr);
    ss >> year >> dash1 >> month >> dash2 >> day;
    return {year, month, day};
}

    auto countOfChars(const string &s) -> int {
    int count = 0;
    for (const auto &ch : s) {
        cout << sizeof(ch) << endl;
        if (ch != '\n' && ch != '\t') ++count;
    }
    return count;
}

    size_t strlen(const std::string &str) {
    size_t size = 0;
    for (auto const byte : str) {
        size += (((byte & 0x80) == 0) || ((byte & 0xC0) == 0xC0));
    }
    return size;
}

    std::wstring stringToWstring(const std::string& str) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

    string getCurrentDate() {
    const std::time_t currentTime = std::time(nullptr);
    const std::tm* localTime = std::localtime(&currentTime);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);

    return std::string(buffer);
}

}