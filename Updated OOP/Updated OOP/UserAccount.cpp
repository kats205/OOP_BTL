#include "UserAccount.h"

UserAccount::UserAccount(const string& accNum, double initialBalance, const string& username,
    const string& phone, const string& pass, const string& pin)
    : Account(accNum, initialBalance), username(username), phoneNumber(phone),
    password(pass), transactionPIN(pin) {
}

string UserAccount::getUserName() const {
    return username;
}

string UserAccount::getPhoneNumber() const {
    return phoneNumber;
}
string UserAccount::getPassword() const {
    return password;
}
string UserAccount::getTransactionPIN() const {
    return transactionPIN;
}

bool UserAccount::getPassword(const string& pass) const {
    return password == pass;
}

bool UserAccount::getTransactionPIN(const string& pin) const {
    return transactionPIN == pin;
}

// Implement phương thức thêm giao dịch
void UserAccount::addTransaction(const Transaction& txn) {
    transactions.push_back(txn);
}

// Implement phương thức lấy lịch sử giao dịch
const vector<Transaction>& UserAccount::getTransactions() const {
    return transactions;
}

void UserAccount::syncBalanceFromHistory() {
    ifstream inFile("userHistory.txt");
    if (!inFile) {
        cerr << "Error opening userHistory.txt for reading!" << endl;
        return;
    }

    string line;
    string phoneNumber, userName, dateTime, txnType, amountStr, balanceStr, details;
    double lastBalance = getBalance(); // Lấy số dư hiện tại từ lớp cơ sở `Account`

    // Duyệt qua file để tìm số dư cuối cùng cho tài khoản này
    while (getline(inFile, line)) {
        istringstream stream(line);
        getline(stream, phoneNumber, '\t');
        getline(stream, userName, '\t');
        getline(stream, dateTime, '\t');
        getline(stream, txnType, '\t');
        getline(stream, amountStr, '\t');
        getline(stream, balanceStr, '\t');
        getline(stream, details, '\t');

        if (phoneNumber == getPhoneNumber()) {
            lastBalance = stod(balanceStr); // Chuyển số dư từ string sang double
        }
    }

    inFile.close();

    // Cập nhật số dư vào lớp cơ sở `Account`
    Account::balance = lastBalance; // Truy cập trực tiếp vào biến `balance` từ lớp cơ sở
}
