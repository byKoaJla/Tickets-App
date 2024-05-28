//
// Created by Denis on 15.05.2024.
//

#pragma once
#include <iomanip>

#include "database.hpp"
#include "utils.hpp"
#include <string>

using namespace std;
class ReservedTicket final : public Db::Atom {
private:
    string _id;
    string _phone;
public:
    Db::S_ticket ticket;

    ReservedTicket() = default;
    explicit ReservedTicket(
        Db::S_ticket ticket,
        string phone
    ) : _phone(std::move(phone)), ticket(std::move(ticket)) {}

    explicit ReservedTicket(
        string id,
        Db::S_ticket ticket,
        string phone
    ) : _id(std::move(id)), _phone(std::move(phone)), ticket(std::move(ticket)) {};

    ~ReservedTicket() override = default;

    void serialize(ostream &os) const override {
        string dDay = ticket.getDay();
        string dTime = ticket.getTime();
        string dest = ticket.getDestination();
        int fSeats = ticket.getSeats();

        os  << _id << " "
            << dDay << " "
            << dTime << " "
            << dest << " "
            << fSeats << " "
            << _phone << endl;
    };

    void deserialize(istream &is) override {
        std::string dDay, dTime, dest;
        int fSeats;
        is >> _id >> dDay >> dTime >> dest >> fSeats >> _phone;
        ticket.setDay(dDay);
        ticket.setTime(dTime);
        ticket.setDestination(dest);
        ticket.setSeats(fSeats);
    };

    [[nodiscard]] string getID() const override {
        return _id;
    };

    void setID(const string &id) override {
        _id = id;
    };

    [[nodiscard]] string getPhone() const {
        return _phone;
    }
    void setPhone(const string &phone) {
        _phone = phone;
    }

    static void bPrint(const ReservedTicket &t) {
        auto [dDay, dTime, dest, fSeats] = t.ticket;

        const std::wstring wId = Utils::stringToWstring(t.getID());
        const std::wstring wDepD = Utils::stringToWstring(dDay);
        const std::wstring wDepT = Utils::stringToWstring(dTime);
        const std::wstring wDest = Utils::stringToWstring(dest);
        const std::wstring wPhone = Utils::stringToWstring(t._phone);

        std::wclog << std::left << std::setfill(L' ') << std::setw(11) << Utils::stringToWstring(t.getID())
            << std::setw(13) << Utils::stringToWstring(t.ticket.getDay())
            << std::setw(11) << Utils::stringToWstring(t.ticket.getTime())
            << std::setw(20) << Utils::stringToWstring(t.ticket.getDestination())
            << std::left << std::setw(10)
            << std::setw(18) << t.ticket.getSeats()
            << std::setw(30) << Utils::stringToWstring(t._phone)
            << endl;

    };

    static list<ReservedTicket> liquidItems(const std::list<ReservedTicket> &items) {
        std::list<ReservedTicket> result;
        for (const auto &t : items) {
            auto dDay = t.ticket.getDay();
            const auto iDay = Utils::parseDate(dDay);

            if (auto [year, month, day] = Utils::parseDate(Utils::getCurrentDate()); iDay.year > year ||
                                                                          (iDay.year == year && iDay.month > month) ||
                                                                          (iDay.year == year && iDay.month == month && iDay.day >= day)) {
                result.push_back(t);
                                                                          }
        }

        return result;
    }

    static bool eq(const ReservedTicket &a, const ReservedTicket &b, const int n) {
        switch (n) {
            case 0: {
                auto [year1, month1, day1] = Utils::parseDate(a.ticket.getDay());
                auto [year2, month2, day2] = Utils::parseDate(b.ticket.getDay());
                if (year1 != year2) {
                    return year1 < year2;
                } else if (month1 != month2) {
                    return month1 < month2;
                } else {
                    return day1 < day2;
                }
            };
            case 1: {
                return Utils::timeToSeconds(a.ticket.getTime()) < Utils::timeToSeconds(b.ticket.getTime());
            };
            case 2: {
                return a.ticket.getDestination().length() < b.ticket.getDestination().length();
            };
            case 3: {
                return a.ticket.getSeats() < b.ticket.getSeats();
            };
            default:
                cerr << "No paraments get thin number: " << n << endl; break;
        }
        return false;
    };
};
