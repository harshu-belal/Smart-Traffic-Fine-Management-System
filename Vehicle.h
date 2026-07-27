#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using std::string;

// Vehicle class stores information about a registered vehicle.
// Data members are private -> this shows ENCAPSULATION.
// Access is only possible through public getters/setters.
class Vehicle {
private:
    string vehicleNumber;
    string ownerName;
    string vehicleType;

public:
    // Default constructor
    Vehicle();

    // Parameterized constructor
    Vehicle(string vNumber, string oName, string vType);

    // Getters
    string getVehicleNumber() const;
    string getOwnerName() const;
    string getVehicleType() const;

    // Setters
    void setOwnerName(string oName);
    void setVehicleType(string vType);

    // Displays vehicle details on console
    void display() const;

    // ---- Menu operations (each talks to vehicles.txt through FileManager) ----
    static void addVehicle();
    static void viewAllVehicles();
    static void searchVehicle();
    static void deleteVehicle();
};

#endif
