#include "Library.h"

int main() {
    Library library;

    // Add books
    library.addBook(Book("12345", "C++ Programming", "Bjarne Stroustrup", 1985, Genre::Nonfiction));
    library.addBook(Book("67890", "Harry Potter", "J.K. Rowling", 1997, Genre::Fiction));

    // Add patrons
    library.addPatron(Patron("Alice", "P123", 0));
    library.addPatron(Patron("Bob", "P456", 50)); // Owes fees

    // Attempt to check out books
    library.checkOutBook("12345", "P123", "2024-12-12"); // Should succeed
    library.checkOutBook("67890", "P456", "2024-12-12"); // Should fail (owes fees)

    // Display patrons with fees
    auto patronsWithFees = library.getPatronsWithFees();
    cout << "Patrons who owe fees:\n";
    for (const auto& name : patronsWithFees) {
        cout << "- " << name << "\n";
    }

    return 0;
}
