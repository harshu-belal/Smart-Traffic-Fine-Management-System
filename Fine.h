#ifndef FINE_H
#define FINE_H

#include <string>
using std::string;

// Fine class represents one traffic challan record.
// It stores which vehicle/driver committed which violation,
// how much fine was charged, and whether it is Paid or Pending.
class Fine {
private:
    string challanId;
    string vehicleNumber;
    string driverName;
    string violationName;
    double fineAmount;
    string paymentStatus;   // "Paid" or "Pending"
    string date;

public:
    // Default constructor
    Fine();

    // Parameterized constructor
    Fine(string cId, string vNum, string dName, string vioName,
         double amount, string status, string dt);

    // Getters
    string getChallanId() const;
    string getVehicleNumber() const;
    string getDriverName() const;
    string getViolationName() const;
    double getFineAmount() const;
    string getPaymentStatus() const;
    string getDate() const;

    void setPaymentStatus(string status);

    // Displays one fine/challan record
    void display() const;

    // ---- Menu operations ----
    static void generateChallan();     // creates a Violation object polymorphically
    static void viewAllFines();
    static void displayTotalFine();
    static void markPayment();         // Fine Management -> mark Paid/Pending
    static void viewPaymentHistory();  // Payment -> view history
    static void generateReports();     // Reports module
};

#endif
