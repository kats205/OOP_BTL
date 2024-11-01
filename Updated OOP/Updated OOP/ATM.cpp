#include "ATM.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

ATM::ATM() : loggedInUser(nullptr) {}

void ATM::registerUser() {
    string phone, username, password, pin;
    cout << "Nhap so dien thoai: ";
    cin >> phone;

    if (!isValidPhoneNumber(phone)) {
        cout << "So dien thoai khong hop le!\n";
        return;
    }

    cout << "Nhap ten nguoi dung: ";
    cin.ignore();
    getline(cin, username);

    cout << "Nhap mat khau: ";
    cin >> password;
    if (!validatePassword(password)) {
        cout << "Mat khau khong hop le!\n";
        return;
    }

    cout << "Nhap ma PIN giao dich: ";
    cin >> pin;

    UserAccount newUser(phone, 0, username, phone, password, pin);
    users.push_back(newUser);
    cout << "Dang ky thanh cong!\n";
}

void ATM::login() {
    string phone, password;
    cout << "Nhap so dien thoai: ";
    cin >> phone;

    for (auto& user : users) {
        if (user.getPhoneNumber() == phone) {
            cout << "Nhap mat khau: ";
            cin >> password;
            if (user.validatePassword(password)) {
                loggedInUser = &user;
                cout << "Dang nhap thanh cong!\n";
                return;
            }
            else {
                cout << "Mat khau khong dung!\n";
                return;
            }
        }
    }
    cout << "So dien thoai khong ton tai!\n";
}

void ATM::logout() {
    if (loggedInUser) {
        loggedInUser = nullptr;
        cout << "Dang xuat thanh cong!\n";
    }
    else {
        cout << "Ban chua dang nhap!\n";
    }
}

void ATM::deposit() {
    if (!loggedInUser) {
        cout << "Ban chua dang nhap!\n";
        return;
    }

    double amount;
    cout << "Nhap so tien can nap: ";
    cin >> amount;
    loggedInUser->deposit(amount);
    cout << "Nap tien thanh cong. So du hien tai: " << loggedInUser->getBalance() << " VND\n";
}

void ATM::withdraw() {
    if (!loggedInUser) {
        cout << "Ban chua dang nhap!\n";
        return;
    }

    double amount;
    cout << "Nhap so tien can rut: ";
    cin >> amount;
    if (loggedInUser->withdraw(amount)) {
        cout << "Rut tien thanh cong. So du hien tai: " << loggedInUser->getBalance() << " VND\n";
    }
    else {
        cout << "So du khong du!\n";
    }
}

void ATM::checkBalance() {
    if (!loggedInUser) {
        cout << "Ban chua dang nhap!\n";
        return;
    }
    cout << "So du cua ban la: " << loggedInUser->getBalance() << " VND\n";
}

bool ATM::isValidPhoneNumber(const string& phone) {
    return phone.length() == 10 && phone.find_first_not_of("0123456789") == string::npos;
}

bool ATM::validatePassword(const string& password) {
    return password.length() >= 6;
}

int ATM::generateOTP() {
    srand(time(0));
    return rand() % 900000 + 100000;
}

void ATM::run() {
    int choice;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Dang ky\n";
        cout << "2. Dang nhap\n";
        cout << "3. Nap tien\n";
        cout << "4. Rut tien\n";
        cout << "5. Kiem tra so du\n";
        cout << "6. Dang xuat\n";
        cout << "0. Thoat\n";
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1: registerUser(); break;
        case 2: login(); break;
        case 3: deposit(); break;
        case 4: withdraw(); break;
        case 5: checkBalance(); break;
        case 6: logout(); break;
        case 0: cout << "Cam on ban da su dung ATM!\n"; break;
        default: cout << "Lua chon khong hop le!\n"; break;
        }
    } while (choice != 0);
}
