#ifndef DRIVER_H
#define DRIVER_H

#include <string>
using std::string;

// Driver class stores information about a registered driver.
// Again, private data members show ENCAPSULATION.
class Driver {
private:
    string driverId;
    string driverName;
    string licenseNumber;
    string vehicleNumber;   // vehicle linked to this driver
    string contactNumber;

public:
    // Default constructor
    Driver();

    // Parameterized constructor
    Driver(string dId, string dName, string license, string vNumber, string contact);

    // Getters
    string getDriverId() const;
    string getDriverName() const;
    string getLicenseNumber() const;
    string getVehicleNumber() const;
    string getContactNumber() const;

    // Displays driver details
    void display() const;

    // ---- Menu operations (talk to drivers.txt through FileManager) ----
    static void addDriver();
    static void viewAllDrivers();
    static void searchDriver();
};

#endif
