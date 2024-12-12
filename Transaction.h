#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Book.h"
#include "Patron.h"
#include <string>

class Transaction {
private:
    Book book;
    Patron patron;
    string activity;
    string date;

public:
    Transaction(Book book, Patron patron, string activity, string date)
        : book(book), patron(patron), activity(activity), date(date) {}

    // Display Transaction details
    friend ostream& operator<<(ostream& os, const Transaction& t) {
        os << "Activity: " << t.activity << "\n"
           << "Date: " << t.date << "\n"
           << t.book << "\n"
           << "Patron: " << t.patron.getUserName() << " (Card: " << t.patron.getCardNumber() << ")\n";
        return os;
    }
};

#endif
