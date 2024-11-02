#pragma once
#include "Account.h"
#include <string>
#include <ctime>   // cho time()
#include <iomanip> // cho setw và setfill
#include <conio.h>
#include <cctype>
using namespace std;

class UserAccount : public Account {
private:
    string username;
    string phoneNumber;
    string password;
    string transactionPIN;

public:
    UserAccount(const string& accNum, double initialBalance, const string& username,
        const string& phone, const string& pass, const string& pin);

    string getUserName() const;
    string getPhoneNumber() const;
    bool validatePassword(const string& pass) const;
    bool validateTransactionPIN(const string& pin) const;
};
