#ifndef PATRON_H
#define PATRON_H

#include <string>
using namespace std;

class Patron {
private:
    string userName;
    string cardNumber;
    int owedFees;

public:
    // Constructor
    Patron(string userName, string cardNumber, int owedFees = 0)
        : userName(userName), cardNumber(cardNumber), owedFees(owedFees) {}

    // Getters
    string getUserName() const { return userName; }
    string getCardNumber() const { return cardNumber; }
    int getOwedFees() const { return owedFees; }

    // Fees-related functions
    bool owesFees() const { return owedFees > 0; }
    void setFees(int fees) { owedFees = fees; }
};

#endif
