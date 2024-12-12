#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Patron.h"
#include "Transaction.h"
#include <vector>
#include <iostream>
#include <algorithm>

class Library {
private:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addPatron(const Patron& patron) {
        patrons.push_back(patron);
    }

    vector<string> getPatronsWithFees() const {
        vector<string> result;
        for (const auto& patron : patrons) {
            if (patron.owesFees()) {
                result.push_back(patron.getUserName());
            }
        }
        return result;
    }

    void checkOutBook(const string& isbn, const string& cardNumber, const string& date) {
        // Find the book
        auto bookIt = find_if(books.begin(), books.end(),
                              [&isbn](const Book& b) { return b.getISBN() == isbn; });

        if (bookIt == books.end()) {
            cout << "Error: Book not found in library.\n";
            return;
        }

        // Check if the book is already checked out
        if (bookIt->isCheckedOut()) {
            cout << "Error: Book is already checked out.\n";
            return;
        }

        // Find the patron
        auto patronIt = find_if(patrons.begin(), patrons.end(),
                                [&cardNumber](const Patron& p) { return p.getCardNumber() == cardNumber; });

        if (patronIt == patrons.end()) {
            cout << "Error: Patron not found in library.\n";
            return;
        }

        // Check if the patron owes fees
        if (patronIt->owesFees()) {
            cout << "Error: Patron owes fees.\n";
            return;
        }

        // Process checkout
        bookIt->checkOut();
        Transaction t(*bookIt, *patronIt, "Check Out", date);
        transactions.push_back(t);
        cout << "Success: Book checked out.\n";
    }
};

#endif
