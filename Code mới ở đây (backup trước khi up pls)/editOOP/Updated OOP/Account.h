#pragma once
#include <string>
using namespace std;

class Account {
protected:
    string accountNumber;
    double balance;

public:
    Account(const string& accNum, double initialBalance);

    virtual void deposit(double amount);
    virtual bool withdraw(double amount);

    double getBalance() const;
    string getAccountNumber() const;

    virtual ~Account() {}
};
