#include "User.h"

using namespace std;

User::User(const string& uname, const string& pword, const string& pin, double bal)
    : username(uname), password(pword), transactionPin(pin), balance(bal) {}

string User::getUsername() const {
    return username;
}

bool User::checkPassword(const string& pword) const {
    return password == pword;
}

bool User::checkPin(const string& pin) const {
    return transactionPin == pin;
}

void User::deposit(double amount) {
    balance += amount;
}

bool User::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

double User::getBalance() const {
    return balance;
}