#pragma once
#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
private:
    string username;
    string password;
    string transactionPin;
    double balance;

public:
    User(const string& uname, const string& pword, const string& pin, double bal = 0.0);
    string getUsername() const;
    bool checkPassword(const string& pword) const;
    bool checkPin(const string& pin) const;
    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;
};

#endif
