#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

// ANSI color codes
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"

using namespace std;

// Enum for genres
enum class Genre {
    Fiction,
    Nonfiction,
    Mystery,
    SciFi,
    Fantasy,
    Biography,
    History
};

// Book class to represent each book
class Book {
public:
    string ISBN;
    string title;
    string author;
    int year;
    Genre genre;

    Book(string ISBN, string title, string author, int year, Genre genre)
        : ISBN(ISBN), title(title), author(author), year(year), genre(genre) {}
};

// Patron class to represent library patrons
class Patron {
public:
    string name;
    string id;
    double fees;

    Patron(string name, string id, double fees)
        : name(name), id(id), fees(fees) {}

    bool owesFees() const {
        return fees > 0;
    }
};

// Library class to manage books and patrons
class Library {
private:
    vector<Book> books;
    vector<Patron> patrons;
    map<string, string> checkedOutBooks;  // ISBN -> Patron ID

public:
    // Add book to library
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Add patron to library
    void addPatron(const Patron& patron) {
        patrons.push_back(patron);
    }

    // Get list of patrons with fees
    vector<string> getPatronsWithFees() {
        vector<string> patronsWithFees;
        for (const auto& patron : patrons) {
            if (patron.owesFees()) {
                patronsWithFees.push_back(patron.name);
            }
        }
        return patronsWithFees;
    }

    // Check out book to patron
    bool checkOutBook(const string& ISBN, const string& patronId, const string& date) {
        auto bookIt = find_if(books.begin(), books.end(), [&ISBN](const Book& book) {
            return book.ISBN == ISBN;
        });

        if (bookIt == books.end()) {
            cout << RED << "[Error] Book with ISBN " << ISBN << " not found.\n" << RESET;
            return false;
        }

        auto patronIt = find_if(patrons.begin(), patrons.end(), [&patronId](const Patron& patron) {
            return patron.id == patronId;
        });

        if (patronIt == patrons.end()) {
            cout << RED << "[Error] Patron with ID " << patronId << " not found.\n" << RESET;
            return false;
        }

        if (patronIt->owesFees()) {
            cout << RED << "[Error] Patron " << patronIt->name << " owes fees and cannot check out books.\n" << RESET;
            return false;
        }

        // Check if book is already checked out
        if (checkedOutBooks.find(ISBN) != checkedOutBooks.end()) {
            cout << RED << "[Error] The book \"" << bookIt->title << "\" is already checked out.\n" << RESET;
            return false;
        }

        checkedOutBooks[ISBN] = patronId;
        cout << GREEN << "[Success] " << patronIt->name << " checked out \"" << bookIt->title << "\" on " << date << ".\n" << RESET;
        return true;
    }

    // Pay fees for a patron
    void payFees(const string& patronId, double amount) {
        auto patronIt = find_if(patrons.begin(), patrons.end(), [&patronId](const Patron& patron) {
            return patron.id == patronId;
        });

        if (patronIt != patrons.end()) {
            patronIt->fees -= amount;
            if (patronIt->fees < 0) patronIt->fees = 0;  // Prevent negative fees
            cout << GREEN << "[Success] " << patronIt->name << " paid " << amount << " in fees.\n" << RESET;
        } else {
            cout << RED << "[Error] Patron with ID " << patronId << " not found.\n" << RESET;
        }
    }

    // Display all books
    void displayBooks() {
        cout << CYAN << "\nList of available books:\n" << RESET;
        for (const auto& book : books) {
            cout << BLUE << "ISBN: " << book.ISBN << RESET << ", " << BOLD << "Title: " << book.title 
                 << RESET << ", Author: " << book.author << ", Year: " << book.year << "\n";
        }
    }

    // Display all patrons
    void displayPatrons() {
        cout << CYAN << "\nList of patrons:\n" << RESET;
        for (const auto& patron : patrons) {
            cout << BLUE << "Name: " << patron.name << RESET << ", ID: " << patron.id 
                 << ", Fees: " << patron.fees << "\n";
        }
    }
};

// Function to display the menu
void displayMenu() {
    cout << CYAN << "\nLibrary Management System\n" << RESET;
    cout << GREEN << "1. Add a Book\n" << RESET;
    cout << GREEN << "2. Add a Patron\n" << RESET;
    cout << GREEN << "3. Check Out a Book\n" << RESET;
    cout << GREEN << "4. Pay Fees\n" << RESET;
    cout << GREEN << "5. Display All Books\n" << RESET;
    cout << GREEN << "6. Display All Patrons\n" << RESET;
    cout << GREEN << "7. Display Patrons with Fees\n" << RESET;
    cout << RED << "8. Exit\n" << RESET;
    cout << "Enter your choice: ";
}

int main() {
    Library library;

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string ISBN, title, author;
                int year;
                int genreInt;
                cout << YELLOW << "Enter book details (ISBN, Title, Author, Year, Genre (0-Fiction, 1-Nonfiction, 2-Mystery, 3-SciFi, 4-Fantasy, 5-Biography, 6-History)):\n" << RESET;
                cin >> ISBN >> title >> author >> year >> genreInt;
                library.addBook(Book(ISBN, title, author, year, static_cast<Genre>(genreInt)));
                break;
            }
            case 2: {
                string name, id;
                double fees;
                cout << YELLOW << "Enter patron details (Name, ID, Fees):\n" << RESET;
                cin >> name >> id >> fees;
                library.addPatron(Patron(name, id, fees));
                break;
            }
            case 3: {
                string ISBN, patronId, date;
                cout << YELLOW << "Enter ISBN, Patron ID, and Date:\n" << RESET;
                cin >> ISBN >> patronId >> date;
                library.checkOutBook(ISBN, patronId, date);
                break;
            }
            case 4: {
                string patronId;
                double amount;
                cout << YELLOW << "Enter Patron ID and amount to pay:\n" << RESET;
                cin >> patronId >> amount;
                library.payFees(patronId, amount);
                break;
            }
            case 5:
                library.displayBooks();
                break;
            case 6:
                library.displayPatrons();
                break;
            case 7: {
                auto patronsWithFees = library.getPatronsWithFees();
                cout << CYAN << "Patrons who owe fees:\n" << RESET;
                for (const auto& name : patronsWithFees) {
                    cout << "- " << name << "\n";
                }
                break;
            }
            case 8:
                cout << RED << "Exiting the system. Goodbye!\n" << RESET;
                return 0;
            default:
                cout << RED << "[Error] Invalid choice, please try again.\n" << RESET;
        }
    }

    return 0;
}
