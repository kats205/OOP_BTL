#pragma once
#include "Account.h"
#include "Transaction.h"
#include <vector>
#include <string>

using namespace std;

class UserAccount : public Account {
private:
    string username;
    string phoneNumber;
    string password;
    string transactionPIN;
    vector<Transaction> transactions;

public:
    UserAccount(const string& accNum, double initialBalance, const string& username,
        const string& phone, const string& pass, const string& pin);

    string getUserName() const;
    string getPhoneNumber() const;
    string getPassword() const;
    string getTransactionPIN() const;

    bool validatePassword(const string& pass) const;
    bool validateTransactionPIN(const string& pin) const;

    void addTransaction(const Transaction& txn);               // Thêm phương thức này
    const vector<Transaction>& getTransactions() const;  // Thêm phương thức này
};
