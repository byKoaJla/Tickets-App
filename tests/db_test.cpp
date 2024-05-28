//
// Created by Denis on 19.05.2024.
//

#include <cassert>
#include "ticket.hpp"

#include "database.hpp"
#include <string>
#include <iostream>

static const string test_db_path = "test_db_path.bin";

static Db::Store<Ticket> ticketStore(test_db_path);

int insertTickets(const int cycle) {
    for (int c = 0; c < cycle; c++) {
        Ticket t {Db::Atom::ObjectID(), {"2024-05-19", "17:09", "Витебск", c}};
        ticketStore.save(t);
    }
    const auto total = ticketStore.loadAll();
    return static_cast<int>(total.size());
}

void insert_tickets_by_know_id(const vector<string> &ids) {
    ticketStore.clearAll();
    for (const auto &id : ids) {
        Ticket _t {id, {"2024-05-20", "10:00", "Минск", 1}};
        ticketStore.save(_t);
    }
}

void insert_tickets_by_know_seats(const int count) {
    for (int c = 0; c < count; c++) {
        Ticket _t  {Db::Atom::ObjectID(), {"2024-05-20", "10:00", "Минск", c}};
        ticketStore.save(_t);
    }
}
//load testing for saving items in db.
void load_testing_save_tickets() {
    int expected = 100;
    int actual = insertTickets(expected);
    //1x-testing
    assert(actual, expected);
    actual = insertTickets(expected*2);
    expected = expected*2;
    //2x-testing
    assert(actual, expected);
    actual = insertTickets(expected*3);
    expected = expected*3;
    //3x-testing
    assert(actual, expected);
}

//load testing for find items in db.
void load_testing_find_by_ids() {
    vector<string> ids;
    list<Ticket> tickets;
    for (int c = 0; c < 100; c++) {
        ids.push_back(Db::Atom::ObjectID());
    }
    insert_tickets_by_know_id(ids);
    for (const auto &id : ids) {
        assert(ticketStore.getItemByID(id).getID() == id);
    }
    ticketStore.clearAll();
}

//load testing for
void load_testing_for_upload_items() {
    int seats = 100;
    int count = 100;
    insert_tickets_by_know_seats(seats);
    for (const auto &t : ticketStore.loadAll()) {
        Ticket _t {{"2024-05-20", "10:00", "Минск", count}};
        ticketStore.updateItemByID(t.getID(), _t);
        assert(t.ticket.getSeats() == count);
        count--;
    }
    ticketStore.clearAll();
}


void teardown() {
    ticketStore.clearAll();
}

int main() {

    load_testing_save_tickets();
    load_testing_find_by_ids();
    load_testing_for_upload_items();

    teardown();
    return 0;
}
