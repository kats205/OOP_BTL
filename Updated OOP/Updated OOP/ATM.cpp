#include "ATM.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

ATM::ATM() : loggedInUser(nullptr) {}

void ATM::run() {
    int choice;
    do {
        displayHeader("<<WELCOME TO W3O BANK>>");
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: registerUser(); 
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            break;
        case 2: login(); 
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            break;
        case 3: cout << "Goodbye!" << endl;
            break;
        default: cout << "Invalid choice, try again." << endl;
            break;
        }
    } while (choice != 3);
}

void ATM::registerUser() {
    displayHeader("Register");
    string username, password, pin;
    string numbers = inputPhoneNumber();
    cout << "Your phone number is valid" << endl;
    cout << "Enter the user name: ";
    //cin.ignore();
    getline(cin, username);
    cout << endl;
    char ch;
    // Nhập mật khẩu với kiểm tra
    do {
        password.clear(); // Xóa mật khẩu để nhập lại nếu không hợp lệ
        bool showPassword = false;
        cout << "Enter password (Press '/' to toggle visibility): ";

        while ((ch = _getch()) != 13) { // Nhấn Enter để kết thúc nhập
            if (ch == 8) { // Nhấn Backspace để xóa ký tự
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b"; // Xóa dấu * trên màn hình
                }
            }
            else if (ch == 127) { // Nhấn Delete để xóa ký tự tiếp theo
                if (!password.empty()) {
                    cout << "\b \b"; // Xóa dấu * trên màn hình
                    password.pop_back();
                }
            }
            else if (ch == '/') { // Nhấn '/' để toggle hiển thị mật khẩu
                showPassword = !showPassword; // Chuyển đổi chế độ hiển thị
                cout << "\n" << (showPassword ? "Password: " : "Password: "); // In lại thông báo
                for (char p : password) {
                    cout << (showPassword ? p : '*'); // Hiển thị mật khẩu hoặc dấu *
                }
                cout << "\nEnter password (Press '/' to toggle visibility): ";
                cout << string(100, ' ') << "\r"; // Xóa dòng con trỏ
                cout << (showPassword ? "Password: " : "Password: "); // In lại thông báo
                for (char p : password) {
                    cout << (showPassword ? p : '*'); // Hiển thị mật khẩu hoặc dấu *
                }
            }
            else {
                password.push_back(ch);
                if (!showPassword) {
                    cout << '*'; // Hiển thị dấu *
                }
                else {
                    cout << ch; // Hiển thị ký tự thật
                }
            }
        }
        cout << endl; // Xuống dòng sau khi nhập xong

        // Kiểm tra mật khẩu sau khi nhập xong
    } while (!validatePassword(password));
    // Nếu đã nhập mật khẩu hợp lệ
    cout << "Password is valid. Password entered successfully!\n";

    cout << endl; // Xuống dòng

    int lent;
    do {
        cout << "Set your transaction PIN(6 digits): ";
        cin >> pin;
        lent = pin.size();
        if (lent != 6) cout << "Your pin just have 6 digits!\n";
    } while (lent != 6);

    cout << endl;

    UserAccount newUser(numbers, 0, username, numbers, password, pin);
    users.push_back(newUser);
    cout << "User registered successfully!\n";
}

void ATM::login() {
    displayHeader("Login");

    if (loggedInUser != nullptr) {
        cout << "You are already logged in.\n";
        return;
    }

    string numbers, password;
    cout << "Enter your phone numbers: ";
    cin >> numbers;
    cout << "Enter password: ";
    char ch;
    while ((ch = _getch()) != 13) { // Nhấn Enter để kết thúc nhập
        if (ch == 8) { // Nhấn Backspace để xóa ký tự
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Xóa dấu * trên màn hình
            }
        }
        else if (ch == 127) { // Nhấn Delete để xóa ký tự tiếp theo
            // Không thực hiện gì nếu không có ký tự nào để xóa
            if (!password.empty()) {
                // Xóa ký tự cuối cùng
                cout << "\b \b"; // Xóa dấu * trên màn hình
                password.pop_back();
            }
        }
        else {
            password.push_back(ch);
            cout << '*'; // Hiển thị dấu *
        }
    }
    cout << endl; // Xuống dòng

    for (UserAccount& user : users) {
        if (user.getPhoneNumber() == numbers && user.validatePassword(password)) {
            loggedInUser = &user;
            cout << "Login successful!\n";
            system("cls");
            loginAfter();
            return;
        }
    }
    cout << "Invalid phone numbers or password.\n";
}

void ATM::loginAfter() {
    int choice;
    do {
        displayHeader("User Login Account");
        showMenuLoginAfter();
        cin >> choice;

        switch (choice) {
        case 1: deposit(); break;
        case 2: withdraw(); break;
        case 3: transfer(); break;
        case 4: checkBalance(); break;
        case 5: cout << "Goodbye!" << endl; break;
        default: cout << "Invalid choice, try again." << endl; break;
        }

        if (choice != 5) {
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 5);
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
    do {
        cout << "Enter your transaction PIN: ";
        cin >> pin;

        if (!loggedInUser->validateTransactionPIN(pin)) {
            cout << "Incorrect PIN. Transaction failed, please re-enter!\n";
        }
    } while (!loggedInUser->validateTransactionPIN(pin));
    
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
    do {
        cout << "Enter your transaction PIN: ";
        cin >> pin;

        if (!loggedInUser->validateTransactionPIN(pin)) {
            cout << "Incorrect PIN. Transaction failed, please re-enter!\n";
        }
    } while (!loggedInUser->validateTransactionPIN(pin));

    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    if (loggedInUser->withdraw(amount)) {
        cout << "Withdrawal successful! Your new balance is: " << loggedInUser->getBalance() << "\n";
    }
    else {
        cout << "Insufficient balance.\n";
    }
}
void ATM::transfer() {
    displayHeader("Transfer");
    if (loggedInUser == nullptr) {
        cout << "Please login first.\n";
        return;
    }

    string receiverNumbers, pin;
    double amount;

    cout << "Enter recipient's phone numbers: ";
    cin >> receiverNumbers;
    cout << "Enter amount to transfer: ";
    cin >> amount;
    do {
        cout << "Enter your transaction PIN: ";
        cin >> pin;

        if (!loggedInUser->validateTransactionPIN(pin)) {
            cout << "Incorrect PIN. Transaction failed, please re-enter!\n";
        }
    } while (!loggedInUser->validateTransactionPIN(pin));

    // Kiểm tra nhập OTP được gửi về máy
    srand(static_cast<unsigned int>(time(0))); // Khởi tạo số ngẫu nhiên gồm 6 chữ số
    int otp = generateOTP(); // Tạo mã OTP
    cout << "An OTP has been sent to your registered device: " << setw(6) << setfill('0') << otp << endl; // Đảm bảo mã OTP luôn có 6 chữ số
    int userInput;
    do {
        cout << "Enter OTP code to confirm money transfer: ";
        cin >> userInput;
        if (userInput == otp) {
            // Kiểm tra người nhận có tồn tại hay không
            bool recipientFound = false;
            for (UserAccount& user : users) {
                if (user.getPhoneNumber() == receiverNumbers) {
                    recipientFound = true;

                    // Kiểm tra nếu người gửi có đủ tiền để chuyển
                    if (loggedInUser->withdraw(amount)) {
                        user.deposit(amount);
                        cout << "\033[1;35m";
                        cout << "\n|================================================================|" << "\n";
                        cout << "\033[1;37m" << "    Transfer to " << user.getUserName() << " successful! -" << amount << "vnd\n";
                        cout << "\033[1;35m";
                        cout << "|----------------------------------------------------------------|" << "\n";
                        cout << "    >>[Receiver]:        " << "\033[1;37m" << user.getPhoneNumber() << "\n";
                        cout << "\033[1;35m";
                        cout << "|----------------------------------------------------------------|" << "\n";
                        cout << "    >>[Recipient Name]: " << "\033[1;37m" << user.getUserName() << "\n";
                        cout << "\033[1;35m";
                        cout << "|----------------------------------------------------------------|" << "\n";
                        cout << "    >>[Amount]:     " << "\033[1;37m" << user.getBalance() << "vnd\n";
                        cout << "\033[1;35m";
                        cout << "|================================================================|" << "\n\n";
                        cout << "\033[0m";
                    }
                    else {
                        cout << "Insufficient balance.\n";
                    }
                    return;
                }
            }
            // Nếu không tìm thấy người nhận
            if (!recipientFound) {
                cout << "Recipient not found.\n";
                return;
            }
        }
        else {
            cout << "Incorrect OTP code, please try again..." << endl;
        }
    } while (userInput != otp);
}

void ATM::checkBalance() {
    displayHeader("Check Balance");
    if (loggedInUser == nullptr) {
        cout << "Please login first.\n";
        return;
    }
    cout << "\033[1;35m";
    cout << "\n|================================================================|" << "\n";
    cout << "    >>[Account]:         " << "\033[1;37m" << loggedInUser->getPhoneNumber() << "\n";
    cout << "\033[1;35m";
    cout << "|----------------------------------------------------------------|" << "\n";
    cout << "    >>[User Name]:         " << "\033[1;37m" << loggedInUser->getUserName() << "\n";
    cout << "\033[1;35m";
    cout << "|----------------------------------------------------------------|" << "\n";
    cout << "    >>[Your balance is]:         " << "\033[1;37m" << loggedInUser->getBalance() << "VND\n";
    cout << "\033[1;35m";
    cout << "|================================================================|" << "\n\n";
    cout << "\033[0m";
}

bool ATM::isValidPhoneNumber(const string& phone) {
    // Kiểm tra nếu số bắt đầu bằng '0' và có độ dài 10 số
    if (phone.length() == 10 && phone[0] == '0') {
        string index2 = phone.substr(0, 2); // Substr dùng để trích chuỗi string với độ dài của chuổi từ vị trí k
        string index3 = phone.substr(0, 3);

        if (index2 == "08" || index2 == "09" || index2 == "03" || index2 == "07" ||
            index3 == "052" || index3 == "056" || index3 == "058" || index3 == "059") {
            return true;
        }
    }
    // Kiểm tra nếu số bắt đầu bằng "+84" và có độ dài 12 số
    else if (phone.length() == 12 && phone.substr(0, 3) == "+84") {
        string index2 = phone.substr(3, 2);
        string index3 = phone.substr(3, 3);

        if (index2 == "08" || index2 == "09" || index2 == "03" || index2 == "07" ||
            index3 == "052" || index3 == "056" || index3 == "058" || index3 == "059") {
            return true;
        }
    }
    return false;
}
string ATM::inputPhoneNumber() {
    string phone;
    do {
        cout << "Enter your phone number: ";
        cin.ignore();
        getline(cin, phone);
        if (!isValidPhoneNumber(phone)) {
            cout << "Invalid phone number format, please try again." << endl;
        }
    } while (!isValidPhoneNumber(phone));
    return phone;
}
bool ATM::validatePassword(const string& password) {
    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    if (password.length() < 10) {
        cout << "Password must be at least 10 characters.\n";
        return false;
    }

    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        if (isdigit(c)) hasDigit = true;
        if (ispunct(c)) hasSpecial = true;  // Ký tự đặc biệt
    }

    if (!hasUpper || !hasDigit || !hasSpecial) {
        cout << "Password must contain at least 1 uppercase character, number and special character. Please re-enter!\n";
        return false;
    }

    return true;
}

int ATM::generateOTP() {
    srand(time(0));
    return rand() % 900000 + 100000;
}

void ATM::displayHeader(const string& title) {
#ifndef DEBUG
    system("cls");  // Reset màn hình
#endif
    cout << "\033[1;36m";  // Màu xanh dương sáng
    cout << "===================================================================================================\n";

    string bankName = "W3O BANK";
    int width = 100; // Độ rộng của khung
    int bankPadding = (width - bankName.length()) / 2;
    cout << "||" << string(bankPadding, ' ') << bankName
        << string(width - bankPadding - bankName.length() - 5, ' ') << "||\n";

    cout << "===================================================================================================\n";

    int titlePadding = (width - title.length()) / 2;
    cout << "||" << string(titlePadding, ' ') << title
        << string(width - titlePadding - title.length() - 5, ' ') << "||\n";

    cout << "===================================================================================================\n";
    cout << "\033[0m";  // Reset lại màu sắc
}
void ATM::showMenu() {
    cout << "\033[1;34m"; // Màu xanh dương sáng cho tiêu đề

    // Căn giữa khung tiêu đề bằng cách thêm khoảng trắng
    cout << "                                        +---------------------+\n";
    cout << "                                        |   W3O BANK MENU     |\n";
    cout << "                                        +---------------------+\n";

    cout << "\033[0m"; // Reset lại màu sắc

    // Khung lựa chọn với các ký tự khác và ngắn hơn
    cout << "\033[1;32m";  // Màu xanh lá sáng cho khung
    cout << "                               +-------------------------------------+\n";
    cout << "                               | 1. Register                         |\n";
    cout << "                               +-------------------------------------+\n";
    cout << "                               | 2. Login                            |\n";
    cout << "                               +-------------------------------------+\n";
    cout << "                               | 3. Exit                             |\n";
    cout << "                               +-------------------------------------+\n";
    cout << "\033[0m"; // Reset lại màu sắc

    cout << ">> Choose an option: ";
}
void ATM::showMenuLoginAfter() {
    cout << "\033[1;34m"; // Màu xanh dương sáng cho tiêu đề

    // Căn giữa khung tiêu đề bằng cách thêm khoảng trắng
    cout << "                                        +---------------------+\n";
    cout << "                                        |   W3O BANK MENU     |\n";
    cout << "                                        +---------------------+\n";

    cout << "\033[0m"; // Reset lại màu sắc

    // Khung lựa chọn với các ký tự khác và ngắn hơn
    cout << "\033[1;32m";  // Màu xanh lá sáng cho khung
    cout << "                               +-------------------------------------+\n";
    cout << "                               | 1. Deposit                          |\n";
    cout << "                               +-------------------------------------+\n";
    cout << "                               | 2. Withdraw                         |\n";
    cout << "                               +-------------------------------------+\n";
    cout << "                               | 3. Transfer                         |\n";
    cout << "                               +-------------------------------------+\n";
    cout << "                               | 4. Check Balance                    |\n";
    cout << "                               +-------------------------------------+\n";
    cout << "                               | 5. Logout                           |\n";
    cout << "                               +-------------------------------------+\n";
    cout << "\033[0m"; // Reset lại màu sắc

    cout << ">> Choose an option: ";
}