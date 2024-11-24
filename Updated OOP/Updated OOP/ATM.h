#pragma once
#include "UserAccount.h"
#include "Transaction.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <filesystem>
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
    bool esc(); //hõ trợ thao tác giao dịch
    bool checkESC();
    bool getInputWithESC(string& input, bool hideInput);
    bool getInputWithESC(double& input);

    //hàm chức năng hõ trợ thời gian, lịch sử, bill
    static string getCurrentDateTime();
    void balanceFluctuation(const UserAccount& user, const Transaction& txn);
    void processPrintBillOption(const Transaction& txn);
    void printBill(const Transaction& txn);

    //hàm hỗ trợ cho kiểm tra dữ liệu đầu vào chuẩn form
    bool isPhoneNumberRegistered(const string& phone);
    string inputPhoneNumber();
    bool validatePhoneNumber(const string& phone);
    bool validateUserName(const string& username);
    bool validatePassword(const string& password);
    bool validatePin(const string& pin);
    bool validateAmount(double amount, const string& transactionType);
    int validateOptionMenu();
    int validateOptionMainMenu(); // 2 hàm hỗ trợ chặn đầu vào cho menu

    int generateOTP();

    // Lưu dữ liệu user vào file
    void loadUsersFromFile();
    void saveUserToFile(const UserAccount& user);
    void saveAllUsersToFile();
};

//hàm ngoài hõ trợ cho việc thiết lập

void gotoxy(int x, int y); // Ko phải phương thức của lớp

//hỗ trợ hiển thị cho lịch sử giao dịch khi in
string shortenName(const string& fullName);
