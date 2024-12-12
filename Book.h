#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
using namespace std;

enum class Genre { Fiction, Nonfiction, Periodical, Biography, Children };

class Book {
private:
    string isbn;
    string title;
    string author;
    int copyrightDate;
    bool checkedOut;
    Genre genre;

public:
    // Constructor
    Book(string isbn, string title, string author, int copyrightDate, Genre genre)
        : isbn(isbn), title(title), author(author), copyrightDate(copyrightDate), checkedOut(false), genre(genre) {}

    // Getters
    string getISBN() const { return isbn; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getCopyrightDate() const { return copyrightDate; }
    bool isCheckedOut() const { return checkedOut; }
    Genre getGenre() const { return genre; }

    // Check out and check in
    void checkOut() { checkedOut = true; }
    void checkIn() { checkedOut = false; }

    // Operator overloads
    bool operator==(const Book& other) const { return isbn == other.isbn; }
    bool operator!=(const Book& other) const { return !(*this == other); }

    // Output stream overload
    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "Title: " << book.title << "\n"
           << "Author: " << book.author << "\n"
           << "ISBN: " << book.isbn << "\n"
           << "Genre: " << (book.genre == Genre::Fiction ? "Fiction" :
                           book.genre == Genre::Nonfiction ? "Nonfiction" :
                           book.genre == Genre::Periodical ? "Periodical" :
                           book.genre == Genre::Biography ? "Biography" : "Children") << "\n";
        return os;
    }
};

#endif
