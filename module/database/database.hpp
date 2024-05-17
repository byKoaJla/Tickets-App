
#pragma once
#include <string>
#include <type_traits>
#include <fstream>
#include <random>
#include <string>
#include <ostream>
#include <list>
#include <iostream>
#include <utility>
#include <ostream>
namespace Db {

    using namespace std;

    struct S_ticket {
        string _day;
        string _time;
        string _destination;
        int _seats;

        S_ticket(string  day, string  time, string  destination, const int seats)
        : _day(std::move(day)), _time(std::move(time)), _destination(std::move(destination)), _seats(seats) {}
        // Конструктор по умолчанию
        S_ticket() : _seats(0) {}

        // Геттеры и сеттеры

        [[nodiscard]] const string& getDay() const { return _day; }
        void setDay(const string& day) { _day = day; }

        [[nodiscard]] const string& getTime() const { return _time; }
        void setTime(const string& time) { _time = time; }

        [[nodiscard]] const string& getDestination() const { return _destination; }
        void setDestination(const string& destination) { _destination = destination; }

        [[nodiscard]] int getSeats() const { return _seats; }
        void setSeats(const int seats) { _seats = seats; }
    };

    class Atom {
    public:
        virtual ~Atom() = default;
        virtual void serialize(ostream &os) const = 0;
        virtual void deserialize(istream &is) = 0;
        [[nodiscard]] virtual string getID() const = 0;
        virtual void setID(const string &id) = 0;

        friend auto operator<<(ostream &os, const Atom &a) -> ostream& {
            a.serialize(os);
            return os;
        };

        friend auto operator>>(istream &is, Atom &a) -> istream& {
            a.deserialize(is);
            return is;
        };

        static string ObjectID() {
            static const string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<> dis(0, static_cast<int>(chars.size() - 1));

            string id(4, 0);
            for (char& c : id) {
                c = chars[dis(gen)];
            }
            return id;
        }
    };

    template <typename St>
    requires std::is_base_of_v<Atom, St>
    class Store {
    private:
        string _path;
        list<St> _liqList;
    public:
        explicit Store(string path): _path(std::move(path)) {};

        void save(const St &item) {
            ifstream cFile(_path, ios::binary);
            if (cFile.good()) {
                St _item;
                while (cFile >> _item) { if (item.getID() == _item.getID()) return; }
                cFile.close();
            }

            ofstream wFile(_path, ios::binary | ios::app);
            if (!wFile) cerr << "Error to open file for to writing: " << _path << endl;
            wFile << item;
            wFile.close();

        }

        list<St> loadAll() {
            list<St> loadedList;
            ifstream rFile(_path, ios::binary);
            if (!rFile) cerr << "Error to read file: " << _path << endl;
            St item;
            while (rFile >> item) {
                loadedList.push_back(item);
            }
            rFile.close();
            return loadedList;
        }

        St getItemByID(const string &id) {
            auto list = loadAll();
            auto it = find_if(list.begin(), list.end(), [&](const St &item) {
                return item.getID() == id;
            });

            if (it != list.end()) {
                return *it;
            } else {
                throw runtime_error("Item not found by this id: " + id);
            }
        }



        void clearAll() const {
            ofstream clFile(_path, ios::out ,ios::trunc);
            if (!clFile) cerr << "Error to open file: " << _path << endl;
            clFile.close();
        }

        void updateItemByID(const string &id, St &newItem) {
            list<St> updatedList;
            list<St> oldList = loadAll();

            bool found = false;

            if (!oldList.empty()) {
                for (const St &o : oldList) {
                    if (o.getID() == id) {
                        St updatedItem = newItem;
                        updatedItem.setID(id);
                        updatedList.push_back(updatedItem);
                        found = true;
                    } else {
                        updatedList.push_back(o);
                    }

                }
                if (!found) {
                    std::cerr << "Element with ID " << id << " not found" << std::endl;
                    updatedList.push_back(newItem);
                }
                oldList = updatedList;
            }

            clearAll();
            ofstream wfile(_path, ios::binary | ios::app);
            if(!wfile) cerr << "Error to write file" << endl;
            for(const auto &o : oldList) {
                wfile << o;
            }
            wfile.close();

        }


        void removeItemByID(const string &id) {
            list<St> list = loadAll();
            find(list.begin(), list.end(), [&](St &it) {
                if (it.getID() == id) {
                    list.erase(it);
                }
            });
            clearAll();
            ofstream wFile(_path, ios::binary | ios::app);
            if (!wFile) cerr << "Error to read file: " << _path << endl;
            for (const auto &it : list) {
                wFile << it;
            }
            wFile.close();
        }
    };
};
