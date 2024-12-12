#include "auth.h"
#include <iostream>
using namespace std;

bool authenticateUser() {
    const string password = "89$#secure@123!"; // Change this password
    string input;
    cout << "\n";
    cout << "\033[36m[Authentication Required]\033[0m Enter password: ";
    cin >> input;
    return input == password;
}
