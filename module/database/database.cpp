//
// Created by Denis on 14.05.2024.
//

#include "database.hpp"

#include <fstream>
#include <random>
#include <string>
#include <ostream>
#include <list>
#include <iostream>
#include <ostream>

namespace Db {
    using namespace std;
    class Atom {
    public:
        virtual ~Atom() = default;
        virtual void serialize(ostream &os) const = 0;
        virtual void deserialize(istream &is) = 0;
        [[nodiscard]] virtual string getID() const = 0;
        virtual void setID(string &id) = 0;

        friend auto &operator<<(ostream &os, const Atom &a) -> ostream& {
            a.serialize(os);
            return os;
        };

        friend auto &operator>>(istream &is, Atom &a) -> istream& {
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
    public:
        explicit Store(const string& path): _path(std::move(_path)) {};

        void save(const St &item) {
            ifstream cFile(_path, ios::binary);
            if (!cFile) cerr << "Error to open file: " << _path << endl;
            St _item;
            while (cFile >> _item) { if (item.getID() == _item.getID()) return; }
            cFile.close();

            ofstream wFile(_path, ios::binary | ios::app);
            if (!wFile) cerr << "Error to open file: " << _path << endl;
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
            auto it = find(list.begin(), list.end(), [&](const St &item) {
                return item.getID() == id;
            });

            if (it != list.end()) {
                return *it;
            }
            else {
                cerr << "No find item by this id: " << id << endl;
            }

            return nullptr;
        }

        void clearAll() const {
            ofstream clFile(_path, ios::out ,ios::trunc);
            if (!clFile) cerr << "Error to open file: " << _path << endl;
            clFile.close();
        }

        void updateItemByID(const string &id, St &newItem) {
            list<St> list = loadAll();
            auto it = find(list.begin(), list.end(), [&](const St item) {
                return item.getID() == id;
            });

            if (it != list.end()) {
                newItem.setID(id);
                *it = newItem;
            } else {
                cerr << "Element with ID " << id << " not found" << endl;
            }

            clearAll();

            ifstream wFile(_path, ios::binary | ios::app);
            if (!wFile) cerr << "Error to open: " << _path << endl;
            for (const auto &item : list) {
                wFile << item;
            }
            wFile.close();
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
