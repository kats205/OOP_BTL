﻿#pragma once
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
    //thao tác người dùng để sử dụng tài khoản
    void run();
    void login();
    void loginAfter();
    void logout();
    void registerUser();
    void enterPassword(string& password);

    //thao tác liên quan đến tiền bạc
    void deposit();
    void withdraw();
    void transfer();
    void transactionHistory(); 
    void checkBalance();

    //hàm chức năng hõ trợ thời gian, lịch sử
    static string getCurrentDateTime();
    void balanceFluctuation(const UserAccount& user, const Transaction& txn);

    //hàm hỗ trợ cho kiểm tra dữ liệu đầu vào chuẩn form
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

//hàm ngoài hõ trợ cho việc thiết lập giao diện
void gotoxy(int x, int y); // Ko phải phương thức của lớp

