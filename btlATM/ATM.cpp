#include "ATM.h"
#include <iostream>
#include <cstdlib>  // Dùng để gọi system("clear") hoặc system("cls")

using namespace std;

ATM::ATM() {
    // Không đọc file, khởi tạo chương trình không cần dữ liệu ban đầu
}

void ATM::displayHeader(const string& title) {
    system("clear || cls");  // Reset màn hình
    cout << "\033[1;36m";  // Màu xanh dương sáng
    cout << "===========================================\n";
    
    // Tên ngân hàng cần căn giữa
    string bankName = "W3O BANK";
    int width = 43;  // Chiều rộng của khung tiêu đề
    int bankPadding = (width - bankName.length()) / 2;  // Tính toán khoảng trắng để căn giữa
    cout << string(bankPadding, ' ') << bankName << "\n";

    cout << "===========================================\n";

    // Tiêu đề cần căn giữa
    int titlePadding = (width - title.length()) / 2;  // Tính toán khoảng trắng để căn giữa
    cout << string(titlePadding, ' ') << title << "\n";

    cout << "===========================================\n";
    cout << "\033[0m";  // Reset lại màu sắc
}


void ATM::run() {
    int choice;
    do {
        displayHeader("Main Menu");
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: login(); break;
        case 2: registerUser(); break;
        case 3: deposit(); break;
        case 4: withdraw(); break;
        case 5: transfer(); break;
        case 6: checkBalance(); break;
        case 7: logout(); break;
        case 8: cout << "Goodbye!" << endl; break;
        default: cout << "Invalid choice, try again." << endl; break;
        }

        if (choice != 8) {
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 8);
}

void ATM::showMenu() {
    cout << "\033[1;34m"; // Màu xanh dương sáng cho tiêu đề

    // Căn giữa khung tiêu đề bằng cách thêm khoảng trắng
    cout << "           +---------------------+\n";
    cout << "           |   W3O BANK MENU     |\n";
    cout << "           +---------------------+\n";

    cout << "\033[0m"; // Reset lại màu sắc

    // Khung lựa chọn với các ký tự khác và ngắn hơn
    cout << "\033[1;32m";  // Màu xanh lá sáng cho khung
    cout << "+-------------------------------------+\n";
    cout << "| 1. Login                            |\n";
    cout << "+-------------------------------------+\n";
    cout << "| 2. Register                         |\n";
    cout << "+-------------------------------------+\n";
    cout << "| 3. Deposit                          |\n";
    cout << "+-------------------------------------+\n";
    cout << "| 4. Withdraw                         |\n";
    cout << "+-------------------------------------+\n";
    cout << "| 5. Transfer                         |\n";
    cout << "+-------------------------------------+\n";
    cout << "| 6. Check Balance                    |\n";
    cout << "+-------------------------------------+\n";
    cout << "| 7. Logout                           |\n";
    cout << "+-------------------------------------+\n";
    cout << "| 8. Exit                             |\n";
    cout << "+-------------------------------------+\n";
    cout << "\033[0m"; // Reset lại màu sắc

    cout << ">> Choose an option: ";
}



void ATM::login() {
    displayHeader("Login");
    if (loggedInUser != nullptr) {
        cout << "You are already logged in.\n";
        return;
    }

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (User& user : users) {
        if (user.getUsername() == username && user.checkPassword(password)) {
            loggedInUser = &user;
            cout << "Login successful!\n";
            return;
        }
    }
    cout << "Invalid username or password.\n";
}

void ATM::registerUser() {
    displayHeader("Register");
    string username, password, pin;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;
    cout << "Set your transaction PIN: ";
    cin >> pin;

    users.push_back(User(username, password, pin));
    cout << "User registered successfully!\n";
}

void ATM::logout() {
    displayHeader("Logout");
    if (loggedInUser == nullptr) {
        cout << "You are not logged in.\n";
        return;
    }
    loggedInUser = nullptr;
    cout << "Logged out successfully.\n";
}

void ATM::deposit() {
    displayHeader("Deposit");
    if (loggedInUser == nullptr) {
        cout << "Please login first.\n";
        return;
    }
    
    string pin;
    cout << "Enter your transaction PIN: ";
    cin >> pin;

    if (!loggedInUser->checkPin(pin)) {
        cout << "Incorrect PIN. Transaction failed.\n";
        return;
    }

    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    loggedInUser->deposit(amount);
    cout << "Deposit successful! Your new balance is: " << loggedInUser->getBalance() << "\n";
}

void ATM::withdraw() {
    displayHeader("Withdraw");
    if (loggedInUser == nullptr) {
        cout << "Please login first.\n";
        return;
    }

    string pin;
    cout << "Enter your transaction PIN: ";
    cin >> pin;

    if (!loggedInUser->checkPin(pin)) {
        cout << "Incorrect PIN. Transaction failed.\n";
        return;
    }

    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    if (loggedInUser->withdraw(amount)) {
        cout << "Withdrawal successful! Your new balance is: " << loggedInUser->getBalance() << "\n";
    } else {
        cout << "Insufficient balance.\n";
    }
}

void ATM::transfer() {
    displayHeader("Transfer");
    if (loggedInUser == nullptr) {
        cout << "Please login first.\n";
        return;
    }

    string receiverUsername, pin;
    double amount;

    cout << "Enter recipient's username: ";
    cin >> receiverUsername;
    cout << "Enter amount to transfer: ";
    cin >> amount;
    cout << "Enter your transaction PIN: ";
    cin >> pin;

    // Kiểm tra mã PIN nhập vào có đúng không
    if (!loggedInUser->checkPin(pin)) {
        cout << "Incorrect PIN. Transaction failed.\n";
        return;
    }

    // Kiểm tra người nhận có tồn tại hay không
    bool recipientFound = false;
    for (User& user : users) {
        if (user.getUsername() == receiverUsername) {
            recipientFound = true;

            // Kiểm tra nếu người gửi có đủ tiền để chuyển
            if (loggedInUser->withdraw(amount)) {
                user.deposit(amount);
                cout << "Transfer successful! Your new balance is: " << loggedInUser->getBalance() << "\n";
            } else {
                cout << "Insufficient balance.\n";
            }
            return;
        }
    }

    // Nếu không tìm thấy người nhận
    if (!recipientFound) {
        cout << "Recipient not found.\n";
    }
}


void ATM::checkBalance() {
    displayHeader("Check Balance");
    if (loggedInUser == nullptr) {
        cout << "Please login first.\n";
        return;
    }
    cout << "Your balance is: " << loggedInUser->getBalance() << "\n";
}
