#include "Fine.h"
#include "FileManager.h"
#include "Violation.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const string FINE_FILE = "fines.txt";
const string PAYMENT_FILE = "payments.txt";
// fines.txt format:
//   challanId|vehicleNumber|driverName|violationName|fineAmount|paymentStatus|date
// payments.txt format:
//   challanId|vehicleNumber|fineAmount|paymentStatus|date

Fine::Fine() {
    fineAmount = 0;
}

Fine::Fine(string cId, string vNum, string dName, string vioName,
           double amount, string status, string dt) {
    challanId = cId;
    vehicleNumber = vNum;
    driverName = dName;
    violationName = vioName;
    fineAmount = amount;
    paymentStatus = status;
    date = dt;
}

string Fine::getChallanId() const { return challanId; }
string Fine::getVehicleNumber() const { return vehicleNumber; }
string Fine::getDriverName() const { return driverName; }
string Fine::getViolationName() const { return violationName; }
double Fine::getFineAmount() const { return fineAmount; }
string Fine::getPaymentStatus() const { return paymentStatus; }
string Fine::getDate() const { return date; }

void Fine::setPaymentStatus(string status) { paymentStatus = status; }

void Fine::display() const {
    cout << "Challan ID     : " << challanId << endl;
    cout << "Vehicle Number : " << vehicleNumber << endl;
    cout << "Driver Name    : " << driverName << endl;
    cout << "Violation      : " << violationName << endl;
    cout << "Fine Amount    : Rs. " << fineAmount << endl;
    cout << "Payment Status : " << paymentStatus << endl;
    cout << "Date           : " << date << endl;
}

// Small helper function (not a class member) to get today's date as text
string getTodayDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string year = to_string(1900 + ltm->tm_year);
    string month = to_string(1 + ltm->tm_mon);
    string day = to_string(ltm->tm_mday);

    return day + "-" + month + "-" + year;
}

// ------------------- Fine / Challan Management -------------------

void Fine::generateChallan() {
    string vNumber, dName;

    cin.ignore();
    cout << "\n--- Generate Traffic Challan ---\n";
    cout << "Enter Vehicle Number : ";
    getline(cin, vNumber);
    cout << "Enter Driver Name    : ";
    getline(cin, dName);

    cout << "\nSelect Violation Type:\n";
    cout << "1. No Helmet\n";
    cout << "2. Overspeeding\n";
    cout << "3. Red Light Jump\n";
    cout << "4. No Seat Belt\n";
    cout << "5. Wrong Parking\n";
    cout << "Enter choice : ";

    int choice;
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid input! Challan not generated.\n";
        return;
    }

    // A base class pointer is used so that the correct derived
    // class object gets called at runtime -> RUNTIME POLYMORPHISM
    Violation *violation = NULL;

    switch (choice) {
        case 1: violation = new NoHelmet();      break;
        case 2: violation = new Overspeeding();  break;
        case 3: violation = new RedLightJump();  break;
        case 4: violation = new NoSeatBelt();    break;
        case 5: violation = new WrongParking();  break;
        default:
            cout << "\nInvalid choice! Challan not generated.\n";
            return;
    }

    // These two calls look identical for every violation type,
    // but each one internally runs the version belonging to the
    // actual derived object that was created above.
    string vioName = violation->getViolationName();
    double amount = violation->getFineAmount();

    // Generate a simple, unique challan ID based on number of existing fines
    vector<string> existingFines = FileManager::readAllLines(FINE_FILE);
    int challanNumber = 0001 + (int)existingFines.size();
    string challanId = "CH" + to_string(challanNumber);

    string todayDate = getTodayDate();
    string status = "Pending";

    string record = challanId + "|" + vNumber + "|" + dName + "|" + vioName + "|" +
                     to_string((int)amount) + "|" + status + "|" + todayDate;
    FileManager::appendLine(FINE_FILE, record);

    cout << "\n----------- Challan Generated -----------\n";
    Fine newFine(challanId, vNumber, dName, vioName, amount, status, todayDate);
    newFine.display();
    cout << "------------------------------------------\n";

    delete violation;   // free the dynamically allocated object
}

void Fine::viewAllFines() {
    vector<string> lines = FileManager::readAllLines(FINE_FILE);

    if (lines.size() == 0) {
        cout << "\nNo fine records found.\n";
        return;
    }

    cout << "\n--- All Traffic Fines ---\n";
    for (int i = 0; i < (int)lines.size(); i++) {
        vector<string> parts = FileManager::splitLine(lines[i], '|');
        if (parts.size() < 7) continue;

        double amount = atof(parts[4].c_str());
        Fine f(parts[0], parts[1], parts[2], parts[3], amount, parts[5], parts[6]);
        cout << "\n[" << i + 1 << "]\n";
        f.display();
    }
}

void Fine::displayTotalFine() {
    vector<string> lines = FileManager::readAllLines(FINE_FILE);
    double total = 0;

    for (int i = 0; i < (int)lines.size(); i++) {
        vector<string> parts = FileManager::splitLine(lines[i], '|');
        if (parts.size() < 7) continue;
        total += atof(parts[4].c_str());
    }

    cout << "\nTotal Fine Amount (Paid + Pending) : Rs. " << total << endl;
}

void Fine::markPayment() {
    string challanId;
    cin.ignore();
    cout << "\nEnter Challan ID to update payment : ";
    getline(cin, challanId);

    vector<string> lines = FileManager::readAllLines(FINE_FILE);
    vector<string> updatedLines;
    bool found = false;

    for (int i = 0; i < (int)lines.size(); i++) {
        vector<string> parts = FileManager::splitLine(lines[i], '|');

        if (parts.size() >= 7 && parts[0] == challanId) {
            found = true;
            cout << "\nCurrent Status : " << parts[5] << endl;
            cout << "1. Mark as Paid\n2. Mark as Pending\nEnter choice : ";
            int choice;
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                choice = 2;   // default to Pending on bad input
            }

            string newStatus = (choice == 1) ? "Paid" : "Pending";
            parts[5] = newStatus;

            // rebuild the line with the updated status
            string newLine = parts[0] + "|" + parts[1] + "|" + parts[2] + "|" +
                              parts[3] + "|" + parts[4] + "|" + parts[5] + "|" + parts[6];
            updatedLines.push_back(newLine);

            // also record this payment update in payments.txt
            string paymentRecord = parts[0] + "|" + parts[1] + "|" + parts[4] + "|" +
                                    newStatus + "|" + getTodayDate();
            FileManager::appendLine(PAYMENT_FILE, paymentRecord);

            cout << "\nPayment status updated to: " << newStatus << endl;
        } else {
            updatedLines.push_back(lines[i]);
        }
    }

    if (found) {
        FileManager::writeAllLines(FINE_FILE, updatedLines);
    } else {
        cout << "\nNo fine found with Challan ID: " << challanId << endl;
    }
}

void Fine::viewPaymentHistory() {
    vector<string> lines = FileManager::readAllLines(PAYMENT_FILE);

    if (lines.size() == 0) {
        cout << "\nNo payment history found.\n";
        return;
    }

    cout << "\n--- Payment History ---\n";
    for (int i = 0; i < (int)lines.size(); i++) {
        vector<string> parts = FileManager::splitLine(lines[i], '|');
        if (parts.size() < 5) continue;

        cout << "\n[" << i + 1 << "]\n";
        cout << "Challan ID     : " << parts[0] << endl;
        cout << "Vehicle Number : " << parts[1] << endl;
        cout << "Fine Amount    : Rs. " << parts[2] << endl;
        cout << "Status         : " << parts[3] << endl;
        cout << "Date           : " << parts[4] << endl;
    }
}

void Fine::generateReports() {
    vector<string> lines = FileManager::readAllLines(FINE_FILE);

    if (lines.size() == 0) {
        cout << "\nNo data available to generate reports.\n";
        return;
    }

    double totalCollected = 0;   // sum of fines marked "Paid"
    double totalPending = 0;     // sum of fines marked "Pending"

    // We use two parallel vectors instead of a map to count
    // violations, keeping the STL usage limited to vector only.
    vector<string> violationNames;
    vector<int> violationCounts;

    for (int i = 0; i < (int)lines.size(); i++) {
        vector<string> parts = FileManager::splitLine(lines[i], '|');
        if (parts.size() < 7) continue;

        double amount = atof(parts[4].c_str());
        string status = parts[5];
        string vioName = parts[3];

        if (status == "Paid") {
            totalCollected += amount;
        } else {
            totalPending += amount;
        }

        // check if this violation name is already in our list
        bool matched = false;
        for (int j = 0; j < (int)violationNames.size(); j++) {
            if (violationNames[j] == vioName) {
                violationCounts[j]++;
                matched = true;
                break;
            }
        }
        if (!matched) {
            violationNames.push_back(vioName);
            violationCounts.push_back(1);
        }
    }

    // find the violation with the highest count
    int maxIndex = 0;
    for (int j = 1; j < (int)violationCounts.size(); j++) {
        if (violationCounts[j] > violationCounts[maxIndex]) {
            maxIndex = j;
        }
    }

    cout << "\n========== Reports ==========\n";
    cout << "Total Fines Collected (Paid)   : Rs. " << totalCollected << endl;
    cout << "Total Fines Pending            : Rs. " << totalPending << endl;
    if (violationNames.size() > 0) {
        cout << "Most Common Violation          : " << violationNames[maxIndex]
             << " (" << violationCounts[maxIndex] << " cases)" << endl;
    }
    cout << "==============================\n";
}
