#ifndef VIOLATION_H
#define VIOLATION_H

#include <string>
using std::string;

// ------------------------------------------------------------------
// Violation is the BASE class for all types of traffic violations.
// getViolationName(), getFineAmount() and display() are declared
// "virtual" so that each derived class can provide its own version.
// This is how we achieve RUNTIME POLYMORPHISM in this project.
// ------------------------------------------------------------------
class Violation {
protected:
    string violationName;
    double fineAmount;

public:
    Violation();                 // default constructor
    virtual string getViolationName() const;
    virtual double getFineAmount() const;
    virtual void display() const;
    virtual ~Violation();         // virtual destructor (good practice)
};

// ---- Derived classes (INHERITANCE) ----
// Each one only sets its own name and fine amount in its constructor.

class NoHelmet : public Violation {
public:
    NoHelmet();
};

class Overspeeding : public Violation {
public:
    Overspeeding();
};

class RedLightJump : public Violation {
public:
    RedLightJump();
};

class NoSeatBelt : public Violation {
public:
    NoSeatBelt();
};

class WrongParking : public Violation {
public:
    WrongParking();
};

#endif
