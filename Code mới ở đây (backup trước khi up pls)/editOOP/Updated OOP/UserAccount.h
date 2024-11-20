#pragma once
#include "Account.h"
#include "Transaction.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


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

    bool getPassword(const string& pass) const;
    bool getTransactionPIN(const string& pin) const;

    void addTransaction(const Transaction& txn);               // Thêm phương thức này
    const vector<Transaction>& getTransactions() const;  // Thêm phương thức này
    void syncBalanceFromHistory(); // Đồng bộ số dư từ file lịch sử giao dịch

};
