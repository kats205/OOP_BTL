#pragma once
#include "UserAccount.h"
#include <vector>

using namespace std;

class ATM {
private:
    vector<UserAccount> users;
    UserAccount* loggedInUser;
public:
    ATM();
    
    void run();
    void login();
    void loginAfter();
    void logout();
    void registerUser();
    void deposit();
    void withdraw();
    void transfer();
    void transactionHistory(); // Thêm hàm 
    void checkBalance();

    static string getCurrentDateTime();
    // Thêm hàm balanceFluctuation
    void balanceFluctuation(const UserAccount& user, const Transaction& txn);

    string inputPhoneNumber();
    bool isValidPhoneNumber(const string& phone);
    bool isPhoneNumberRegistered(const string& phone);
    bool validatePassword(const string& password);

    int generateOTP();

    // Lưu dữ liệu user vào file
    void loadUsersFromFile();
    void saveUserToFile(const UserAccount& user);
    void saveAllUsersToFile();
};

