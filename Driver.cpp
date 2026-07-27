#include "Driver.h"
#include "FileManager.h"
#include <iostream>

using namespace std;

const string DRIVER_FILE = "drivers.txt";

Driver::Driver() {
    driverId = "";
    driverName = "";
    licenseNumber = "";
    vehicleNumber = "";
    contactNumber = "";
}

Driver::Driver(string dId, string dName, string license, string vNumber, string contact) {
    driverId = dId;
    driverName = dName;
    licenseNumber = license;
    vehicleNumber = vNumber;
    contactNumber = contact;
}

string Driver::getDriverId() const { return driverId; }
string Driver::getDriverName() const { return driverName; }
string Driver::getLicenseNumber() const { return licenseNumber; }
string Driver::getVehicleNumber() const { return vehicleNumber; }
string Driver::getContactNumber() const { return contactNumber; }

void Driver::display() const {
    cout << "Driver ID       : " << driverId << endl;
    cout << "Driver Name     : " << driverName << endl;
    cout << "License Number  : " << licenseNumber << endl;
    cout << "Vehicle Number  : " << vehicleNumber << endl;
    cout << "Contact Number  : " << contactNumber << endl;
}

// Driver Management Menu Options 

void Driver::addDriver() {
    string dId, dName, license, vNumber, contact;

    cin.ignore();
    cout << "\n--- Add New Driver ---\n";
    cout << "Enter Driver ID       : "; getline(cin, dId);
    cout << "Enter Driver Name     : "; getline(cin, dName);
    cout << "Enter License Number  : "; getline(cin, license);
    cout << "Enter Vehicle Number  : "; getline(cin, vNumber);
    cout << "Enter Contact Number  : "; getline(cin, contact);

    string record = dId + "|" + dName + "|" + license + "|" + vNumber + "|" + contact;
    FileManager::appendLine(DRIVER_FILE, record);

    cout << "\nDriver added successfully!\n";
}

void Driver::viewAllDrivers() {
    vector<string> lines = FileManager::readAllLines(DRIVER_FILE);

    if (lines.size() == 0) {
        cout << "\nNo drivers found.\n";
        return;
    }

    cout << "\n--- All Registered Drivers ---\n";
    for (int i = 0; i < (int)lines.size(); i++) {
        vector<string> parts = FileManager::splitLine(lines[i], '|');
        if (parts.size() < 5) continue;

        Driver d(parts[0], parts[1], parts[2], parts[3], parts[4]);
        cout << "\n[" << i + 1 << "]\n";
        d.display();
    }
}

void Driver::searchDriver() {
    string searchKey;
    cin.ignore();
    cout << "\nEnter Driver ID or License Number to search : ";
    getline(cin, searchKey);

    vector<string> lines = FileManager::readAllLines(DRIVER_FILE);
    bool found = false;

    for (int i = 0; i < (int)lines.size(); i++) {
        vector<string> parts = FileManager::splitLine(lines[i], '|');
        if (parts.size() < 5) continue;

        if (parts[0] == searchKey || parts[2] == searchKey) {
            Driver d(parts[0], parts[1], parts[2], parts[3], parts[4]);
            cout << "\nDriver Found:\n";
            d.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nNo driver found with ID/License: " << searchKey << endl;
    }
}
