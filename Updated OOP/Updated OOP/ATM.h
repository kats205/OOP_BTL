#pragma once
#include <vector>
#include "UserAccount.h"
using namespace std;

class ATM {
private:
    vector<UserAccount> users;
    UserAccount* loggedInUser;

public:
    ATM();

    void run();
    void login();
    void logout();
    void registerUser();
    void deposit();
    void withdraw();
    void transfer();
    void checkBalance();
    bool isValidPhoneNumber(const string& phone);
    string inputPhoneNumber();
    bool validatePassword(const string& password);
    int generateOTP();
};
