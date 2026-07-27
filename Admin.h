#ifndef ADMIN_H
#define ADMIN_H

#include <string>
using std::string;

class Admin {
private:
    string username;
    string password;

public:
    Admin();          // sets the hardcoded username/password
    bool login();      // returns true if login is successful
};

#endif
