#pragma once

#include "database.hpp"

#include <iomanip>
#include <utility>
#include "database.hpp"
#include "utils.hpp"
using namespace std;


class Ticket final : public Db::Atom {
private:
    string _id;
public:
    Db::S_ticket ticket;
    explicit Ticket(Db::S_ticket ticket) : ticket(std::move(ticket)) {};
    explicit Ticket(string id, Db::S_ticket ticket): _id(std::move(id)), ticket(std::move(ticket)) {}

    ~Ticket() override = default;

    void serialize(ostream &os) const override {
        auto [dDay, dTime, dest, fSeats] = ticket;
        os  << _id << " "
            << dDay << " "
            << dTime << " "
            << dest << " "
            << fSeats << endl;
    };

    void deserialize(istream &is) override {
        auto [dDay, dTime, dest, fSeats] = ticket;
        is >> _id >> dDay >> dTime >> dest >> fSeats;
    };

    [[nodiscard]] string getID() const override {
        return _id;
    };

    void setID(string &id) override {
        _id = id;
    };

    static void bPrint(const Ticket &t) {
        auto [dDay, dTime, dest, fSeats] = t.ticket;

        const std::wstring wId = Utils::stringToWstring(t.getID());
        const std::wstring wDepD = Utils::stringToWstring(dDay);
        const std::wstring wDepT = Utils::stringToWstring(dTime);
        const std::wstring wDest = Utils::stringToWstring(dest);

        std::wcout << std::left << std::setfill(L' ') << std::setw(10) << wId
                  << std::setw(12) << wDepD
                  << std::setw(10) << wDepT
                  << std::setw(19) << wDest
                  << std::left << std::setw(10) << fSeats << std::endl;
    };

    static list<Ticket> liquidItems(const std::list<Ticket> &items) {
        std::list<Ticket> result;
        for (const auto &t : items) {
            auto dDay = t.ticket.departureDay;
            const auto iDay = Utils::parseDate(dDay);

            if (auto [year, month, day] = Utils::parseDate(Utils::getCurrentDate()); iDay.year > year ||
                                                                          (iDay.year == year && iDay.month > month) ||
                                                                          (iDay.year == year && iDay.month == month && iDay.day >= day)) {
                result.push_back(t);
                }
        }

        return result;
    }

    bool eq(Ticket &a, Ticket &b, const int n) {
        switch (n) {
            case 0: {
                auto [year1, month1, day1] = Utils::parseDate(a.ticket.departureDay);
                auto [year2, month2, day2] = Utils::parseDate(b.ticket.departureDay);
                if (year1 != year2) {
                    return year1 < year2;
                } else if (month1 != month2) {
                    return month1 < month2;
                } else {
                    return day1 < day2;
                }
            };
            case 1: {
                return Utils::timeToSeconds(a.ticket.departureTime) < Utils::timeToSeconds(b.ticket.departureTime);
            };
            case 2: {
                return a.ticket.destination.length() < b.ticket.destination.length();
            };
            case 3: {
                return a.ticket.freeSeats < b.ticket.freeSeats;
            };
            default:
                cerr << "No paraments get thin number: " << n << endl; break;
        }
        return false;
    };

};