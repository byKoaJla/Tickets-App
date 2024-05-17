#pragma once

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
    Ticket() = default;
    explicit Ticket(Db::S_ticket ticket) : ticket(std::move(ticket)) {};
    explicit Ticket(string id, Db::S_ticket ticket): _id(std::move(id)), ticket(std::move(ticket)) {}

    ~Ticket() override = default;

    void serialize(std::ostream &os) const override {
        string dDay = ticket.getDay();
        string dTime = ticket.getTime();
        string dest = ticket.getDestination();
        int fSeats = ticket.getSeats();

        os << _id << " "
           << dDay << " "
           << dTime << " "
           << dest << " "
           << fSeats << std::endl;
    }
    void deserialize(istream &is) override {
        std::string dDay, dTime, dest;
        int fSeats;
        is >> _id >> dDay >> dTime >> dest >> fSeats;
        ticket.setDay(dDay);
        ticket.setTime(dTime);
        ticket.setDestination(dest);
        ticket.setSeats(fSeats);
    };

    [[nodiscard]] string getID() const override {
        return _id;
    };

    void setID(string &id) override {
        _id = id;
    };

    static void bPrint(const Ticket &t) {
        std::wclog << std::left << std::setfill(L' ') << std::setw(11) << Utils::stringToWstring(t.getID())
                   << std::setw(14) << Utils::stringToWstring(t.ticket.getDay())
                   << std::setw(10) << Utils::stringToWstring(t.ticket.getTime())
                   << std::setw(19) << Utils::stringToWstring(t.ticket.getDestination())
                   << std::left << std::setw(10) << t.ticket.getSeats() << std::endl;
    }

    static list<Ticket> liquidItems(const std::list<Ticket> &items) {
        std::list<Ticket> result;
        for (const auto t : items) {
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

    static bool eq(const Ticket &a, const Ticket &b, const int n) {
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