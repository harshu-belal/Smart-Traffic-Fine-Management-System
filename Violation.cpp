#include "Violation.h"
#include <iostream>

using namespace std;

// ---------------- Base class Violation ----------------

Violation::Violation() {
    violationName = "Unknown";
    fineAmount = 0.0;
}

string Violation::getViolationName() const {
    return violationName;
}

double Violation::getFineAmount() const {
    return fineAmount;
}

void Violation::display() const {
    cout << "Violation Type : " << violationName << endl;
    cout << "Fine Amount    : Rs. " << fineAmount << endl;
}

Violation::~Violation() {
   
}

NoHelmet::NoHelmet() {
    violationName = "No Helmet";
    fineAmount = 500;
}

Overspeeding::Overspeeding() {
    violationName = "Overspeeding";
    fineAmount = 1000;
}

RedLightJump::RedLightJump() {
    violationName = "Red Light Jump";
    fineAmount = 1500;
}

NoSeatBelt::NoSeatBelt() {
    violationName = "No Seat Belt";
    fineAmount = 500;
}

WrongParking::WrongParking() {
    violationName = "Wrong Parking";
    fineAmount = 300;
}
