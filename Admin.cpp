#include "Admin.h"
#include <iostream>

using namespace std;

Admin::Admin() {
    username = "gehu";
    password = "harshu123";
}

bool Admin::login() {
    string inputUser, inputPass;

    cout << "\n===== Admin Login =====\n";
    cout << "Username : ";
    cin >> inputUser;
    cout << "Password : ";
    cin >> inputPass;

    if (inputUser == username && inputPass == password) {
        cout << "\nLogin successful! Welcome, Admin.\n";
        return true;
    } else {
        cout << "\nInvalid username or password.\n";
        return false;
    }
}
