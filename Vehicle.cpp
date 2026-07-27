#include "Vehicle.h"
#include "FileManager.h"
#include <iostream>

using namespace std;

const string VEHICLE_FILE = "vehicles.txt";
// Record format stored in the file:  vehicleNumber|ownerName|vehicleType

Vehicle::Vehicle() {
    vehicleNumber = "";
    ownerName = "";
    vehicleType = "";
}

Vehicle::Vehicle(string vNumber, string oName, string vType) {
    vehicleNumber = vNumber;
    ownerName = oName;
    vehicleType = vType;
}

string Vehicle::getVehicleNumber() const { return vehicleNumber; }
string Vehicle::getOwnerName() const { return ownerName; }
string Vehicle::getVehicleType() const { return vehicleType; }

void Vehicle::setOwnerName(string oName) { ownerName = oName; }
void Vehicle::setVehicleType(string vType) { vehicleType = vType; }

void Vehicle::display() const {
    cout << "Vehicle Number : " << vehicleNumber << endl;
    cout << "Owner Name     : " << ownerName << endl;
    cout << "Vehicle Type   : " << vehicleType << endl;
}

// ------------------- Vehicle Management Menu Options -------------------

void Vehicle::addVehicle() {
    string vNumber, oName, vType;

    cin.ignore();  // clear leftover newline from previous cin >>
    cout << "\n--- Add New Vehicle ---\n";
    cout << "Enter Vehicle Number : ";
    getline(cin, vNumber);
    cout << "Enter Owner Name     : ";
    getline(cin, oName);
    cout << "Enter Vehicle Type (Car/Bike/Truck) : ";
    getline(cin, vType);

    // Build one line record and append it to the text file
    string record = vNumber + "|" + oName + "|" + vType;
    FileManager::appendLine(VEHICLE_FILE, record);

    cout << "\nVehicle added successfully!\n";
}

void Vehicle::viewAllVehicles() {
    vector<string> lines = FileManager::readAllLines(VEHICLE_FILE);

    if (lines.size() == 0) {
        cout << "\nNo vehicles found.\n";
        return;
    }

    cout << "\n--- All Registered Vehicles ---\n";
    for (int i = 0; i < (int)lines.size(); i++) {
        vector<string> parts = FileManager::splitLine(lines[i], '|');
        if (parts.size() < 3) continue;   // skip a broken/incomplete line

        Vehicle v(parts[0], parts[1], parts[2]);
        cout << "\n[" << i + 1 << "]\n";
        v.display();
    }
}

void Vehicle::searchVehicle() {
    string searchNumber;
    cin.ignore();
    cout << "\nEnter Vehicle Number to search : ";
    getline(cin, searchNumber);

    vector<string> lines = FileManager::readAllLines(VEHICLE_FILE);
    bool found = false;

    for (int i = 0; i < (int)lines.size(); i++) {
        vector<string> parts = FileManager::splitLine(lines[i], '|');
        if (parts.size() < 3) continue;

        if (parts[0] == searchNumber) {
            Vehicle v(parts[0], parts[1], parts[2]);
            cout << "\nVehicle Found:\n";
            v.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nNo vehicle found with number: " << searchNumber << endl;
    }
}

void Vehicle::deleteVehicle() {
    string delNumber;
    cin.ignore();
    cout << "\nEnter Vehicle Number to delete : ";
    getline(cin, delNumber);

    vector<string> lines = FileManager::readAllLines(VEHICLE_FILE);
    vector<string> updatedLines;
    bool found = false;

    for (int i = 0; i < (int)lines.size(); i++) {
        vector<string> parts = FileManager::splitLine(lines[i], '|');
        if (parts.size() >= 1 && parts[0] == delNumber) {
            found = true;
            continue;   // do not copy this line -> effectively deletes it
        }
        updatedLines.push_back(lines[i]);
    }

    if (found) {
        FileManager::writeAllLines(VEHICLE_FILE, updatedLines);
        cout << "\nVehicle deleted successfully.\n";
    } else {
        cout << "\nVehicle not found.\n";
    }
}
