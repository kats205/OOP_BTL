#pragma once
#ifndef ATM_H
#define ATM_H

#include "User.h"
#include <vector>
#include <string>
#include <regex>

using namespace std;

class ATM {
private:
    vector<User> users;      // Danh sách người dùng
    User* loggedInUser = nullptr; // Người dùng hiện tại (nếu có)

    void showMenu();
    void displayHeader(const string& title); 

public:
    ATM();
    void run();
    void login();
    void registerUser();
    bool validatePassword(const string& password);
    void logout();
    void deposit();       // Nạp tiền
    void withdraw();      // Rút tiền
    void transfer();      // Chuyển tiền với mã pin
    int generateOTP();
    void checkBalance();  // Xem số dư
    bool isValidPhoneNumber(const string& numbers);

};

#endif
