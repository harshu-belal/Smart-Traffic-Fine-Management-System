#include <iostream>
#include "Admin.h"
#include "Vehicle.h"
#include "Driver.h"
#include "Fine.h"

using namespace std;

// Sub-menu function declarations
void vehicleMenu();
void driverMenu();
void fineMenu();
void paymentMenu();
void reportMenu();

int main() {
    Admin admin;   
    bool loggedIn = false;
    int attempts = 0;

    cout << "===================================================\n";
    cout << "   SMART TRAFFIC FINE MANAGEMENT SYSTEM\n";
    cout << "===================================================\n";

    // Allow up to 3 login attempts
    while (!loggedIn && attempts < 3) {
        loggedIn = admin.login();
        attempts++;
        if (!loggedIn && attempts < 3) {
            cout << "Attempts left: " << (3 - attempts) << endl;
        }
    }

    if (!loggedIn) {
        cout << "\nToo many failed attempts. Exiting program.\n";
        return 0;
    }

    int mainChoice;

    do {
        cout << "\n=================== MAIN MENU ===================\n";
        cout << "1. Vehicle Management\n";
        cout << "2. Driver Management\n";
        cout << "3. Fine Management (Violations & Challan)\n";
        cout << "4. Payment\n";
        cout << "5. Reports\n";
        cout << "6. Exit\n";
        cout << "==================================================\n";
        cout << "Enter your choice : ";
        cin >> mainChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (mainChoice) {
            case 1: vehicleMenu(); break;
            case 2: driverMenu();  break;
            case 3: fineMenu();    break;
            case 4: paymentMenu(); break;
            case 5: reportMenu();  break;
            case 6: cout << "\nThank you for using the system. Goodbye!\n"; break;
            default: cout << "\nInvalid choice, please try again.\n";
        }

    } while (mainChoice != 6);

    return 0;
}

// Vehicle Management Sub-menu
void vehicleMenu() {
    int choice;
    do {
        cout << "\n----- Vehicle Management -----\n";
        cout << "1. Add Vehicle\n";
        cout << "2. View All Vehicles\n";
        cout << "3. Search Vehicle\n";
        cout << "4. Delete Vehicle\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice : ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: Vehicle::addVehicle();       break;
            case 2: Vehicle::viewAllVehicles();  break;
            case 3: Vehicle::searchVehicle();    break;
            case 4: Vehicle::deleteVehicle();    break;
            case 5: cout << "\nReturning to Main Menu...\n"; break;
            default: cout << "\nInvalid choice, please try again.\n";
        }
    } while (choice != 5);
}

// Driver Management Sub-menu 
void driverMenu() {
    int choice;
    do {
        cout << "\n----- Driver Management -----\n";
        cout << "1. Add Driver\n";
        cout << "2. View All Drivers\n";
        cout << "3. Search Driver\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice : ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: Driver::addDriver();      break;
            case 2: Driver::viewAllDrivers(); break;
            case 3: Driver::searchDriver();   break;
            case 4: cout << "\nReturning to Main Menu...\n"; break;
            default: cout << "\nInvalid choice, please try again.\n";
        }
    } while (choice != 4);
}

// Fine Management Sub-menu
void fineMenu() {
    int choice;
    do {
        cout << "\n----- Fine Management -----\n";
        cout << "1. Generate Challan (Add Violation + Fine)\n";
        cout << "2. View All Fines\n";
        cout << "3. Display Total Fine Amount\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice : ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: Fine::generateChallan();   break;
            case 2: Fine::viewAllFines();      break;
            case 3: Fine::displayTotalFine();  break;
            case 4: cout << "\nReturning to Main Menu...\n"; break;
            default: cout << "\nInvalid choice, please try again.\n";
        }
    } while (choice != 4);
}

// Payment Sub-menu 
void paymentMenu() {
    int choice;
    do {
        cout << "\n----- Payment -----\n";
        cout << "1. Mark Fine as Paid / Pending\n";
        cout << "2. View Payment History\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice : ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: Fine::markPayment();        break;
            case 2: Fine::viewPaymentHistory(); break;
            case 3: cout << "\nReturning to Main Menu...\n"; break;
            default: cout << "\nInvalid choice, please try again.\n";
        }
    } while (choice != 3);
}

// Reports Sub-menu 
void reportMenu() {
    int choice;
    do {
        cout << "\n----- Reports -----\n";
        cout << "1. Show Full Report (Collected / Pending / Most Common Violation)\n";
        cout << "2. Back to Main Menu\n";
        cout << "Enter your choice : ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: Fine::generateReports(); break;
            case 2: cout << "\nReturning to Main Menu...\n"; break;
            default: cout << "\nInvalid choice, please try again.\n";
        }
    } while (choice != 2);
}
