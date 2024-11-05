#pragma once
#include "UserAccount.h"
#include <vector>
#include <windows.h>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <sstream>
#include <string>
#include <cstdlib>
#include <fstream>
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
    void transactionHistory(); 
    void checkBalance();

    static string getCurrentDateTime();
    void balanceFluctuation(const UserAccount& user, const Transaction& txn);

    bool isPhoneNumberRegistered(const string& phone);
    string inputPhoneNumber();
    bool validatePhoneNumber(const string& phone);
    bool validatePassword(const string& password);
    bool validateAmount(double amount, const string& transactionType);

    int generateOTP();

    // Lưu dữ liệu user vào file
    void loadUsersFromFile();
    void saveUserToFile(const UserAccount& user);
    void saveAllUsersToFile();
};

void gotoxy(int x, int y); // Ko phải phương thức của lớp

