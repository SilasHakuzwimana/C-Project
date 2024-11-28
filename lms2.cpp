#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

enum Genre { fiction, nonfiction, periodical, biography, children };

class Book {
private:
    string ISBN;
    string title;
    string author;
    int copyright_date;
    bool checked_out;
    Genre genre;

public:
    Book(string isbn, string t, string a, int date, Genre g)
        : ISBN(isbn), title(t), author(a), copyright_date(date), checked_out(false), genre(g) {}

    string getISBN() const { return ISBN; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getCopyrightDate() const { return copyright_date; }
    bool isCheckedOut() const { return checked_out; }
    Genre getGenre() const { return genre; }

    void checkOut() { checked_out = true; }
    void checkIn() { checked_out = false; }

    bool operator==(const Book& other) const { return ISBN == other.ISBN; }
    bool operator!=(const Book& other) const { return ISBN != other.ISBN; }

    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "Title: " << book.title << "\n"
           << "Author: " << book.author << "\n"
           << "ISBN: " << book.ISBN << "\n"
           << "Genre: " << book.genre << endl;
        return os;
    }
};

class Patron {
private:
    string username;
    string card_number;
    int owed_fees;

public:
    Patron(string uname, string cardnum)
        : username(uname), card_number(cardnum), owed_fees(0) {}

    string getUsername() const { return username; }
    string getCardNumber() const { return card_number; }
    int getOwedFees() const { return owed_fees; }

    bool owesFees() const { return owed_fees > 0; }
    void setFees(int fees) { owed_fees = fees; }
};

class Transaction {
public:
    Book book;
    Patron patron;
    string activity;
    string date;

    Transaction(Book b, Patron p, string act, string d)
        : book(b), patron(p), activity(act), date(d) {}
};

class Library {
private:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;

public:
    void addBook(const Book& book) { books.push_back(book); }
    void addPatron(const Patron& patron) { patrons.push_back(patron); }

    void checkOutBook(const string& isbn, const string& card_number, const string& date) {
        auto bookIt = find_if(books.begin(), books.end(),
                              [&isbn](const Book& b) { return b.getISBN() == isbn; });
        auto patronIt = find_if(patrons.begin(), patrons.end(),
                                [&card_number](const Patron& p) { return p.getCardNumber() == card_number; });

        if (bookIt == books.end()) throw runtime_error("Book not found in the library.");
        if (patronIt == patrons.end()) throw runtime_error("Patron not found in the library.");
        if (patronIt->owesFees()) throw runtime_error("Patron owes fees to the library.");

        bookIt->checkOut();
        transactions.push_back(Transaction(*bookIt, *patronIt, "check out", date));
    }

    vector<string> patronsWhoOweFees() const {
        vector<string> result;
        for (const auto& patron : patrons) {
            if (patron.owesFees()) result.push_back(patron.getUsername());
        }
        return result;
    }
};

int main() {
    Library library;

    library.addBook(Book("12345", "C++ Programming", "Bjarne Stroustrup", 1985, Genre::nonfiction));
    library.addBook(Book("67890", "Harry Potter", "J.K. Rowling", 1997, Genre::fiction));

    library.addPatron(Patron("Alice", "0001"));
    library.addPatron(Patron("Bob", "0002"));

    try {
        library.checkOutBook("12345", "0001", "2024-11-20");
        cout << "Book checked out successfully." << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    vector<string> patrons_owing_fees = library.patronsWhoOweFees();
    if (!patrons_owing_fees.empty()) {
        cout << "Patrons who owe fees:" << endl;
        for (const auto& name : patrons_owing_fees) {
            cout << name << endl;
        }
    } else {
        cout << "No patrons owe fees." << endl;
    }

    return 0;
}