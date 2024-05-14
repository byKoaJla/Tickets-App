#pragma once
#include <string>

using namespace std;
namespace Utils {
    string rusUp2Down(const std::string &str);

    string getDayOfWeek(const std::string& day);

    int timeToSeconds(const std::string &timeStr);

    struct Date { int year, month, day; };

    Date parseDate(const std::string& dateStr);

    auto countOfChars(const string &s) -> int;

    size_t strlen(const std::string &str);

    std::wstring stringToWstring(const std::string& str);

    string getCurrentDate();
}