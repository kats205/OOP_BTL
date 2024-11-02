#include "UserAccount.h"

UserAccount::UserAccount(const string& accNum, double initialBalance, const string& username,
    const string& phone, const string& pass, const string& pin)
    : Account(accNum, initialBalance), username(username), phoneNumber(phone),
    password(pass), transactionPIN(pin) {}

string UserAccount::getUserName() const {
    return username;
}

string UserAccount::getPhoneNumber() const {
    return phoneNumber;
}

bool UserAccount::validatePassword(const string& pass) const {
    return password == pass;
}

bool UserAccount::validateTransactionPIN(const string& pin) const {
    return transactionPIN == pin;
}

