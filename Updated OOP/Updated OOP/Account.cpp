#include "Account.h"

Account::Account(const string& accNum, double initialBalance)
    : accountNumber(accNum), balance(initialBalance) {}

void Account::deposit(double amount) {
    balance += amount;
}

bool Account::withdraw(double amount) {
    if (amount > balance) {
        return false;
    }
    balance -= amount;
    return true;
}

double Account::getBalance() const {
    return balance;
}

string Account::getAccountNumber() const {
    return accountNumber;
}
