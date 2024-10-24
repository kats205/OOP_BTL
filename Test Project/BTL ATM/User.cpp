#include "User.h"

using namespace std;

User::User(const string& num, const string& pword, const string& pin, double bal)
    : numbers(num), password(pword), transactionPin(pin), balance(bal) {}

string User::getNumbers() const {
    return numbers;
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
