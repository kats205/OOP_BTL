#include "ATM.h"
#include "Menu.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream> 
using namespace std;

ATM::ATM() : loggedInUser(nullptr) {}

void ATM::run() {

    

    int choice;
    do {
        Menu::displayHeader("<<WELCOME TO W3O BANK>>");
        loadUsersFromFile();  // Load users from file at startup
        Menu::showMenu();
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
    Menu::displayHeader("Register");
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
    saveUserToFile(newUser);  // Lưu người dùng vào tệp

    cout << "User registered successfully!\n";
}

void ATM::login() {
    Menu::displayHeader("Login");

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
        Menu::displayHeader("User Login Account");
        Menu::showMenuLoginAfter();
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
    Menu::displayHeader("Logout");
    if (loggedInUser == nullptr) {
        cout << "You are not logged in.\n";
        return;
    }
    loggedInUser = nullptr;
    cout << "Logged out successfully.\n";
}

void ATM::deposit() {
    Menu::displayHeader("Deposit");
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
        if (amount < 0) cout << "Sorry, the deposit amount can not be negative, please try again!\n";
        return;
    
    loggedInUser->deposit(amount);
    cout << "Deposit successful! Your new balance is: " << loggedInUser->getBalance() << "\n";
    saveAllUsersToFile();
}

void ATM::withdraw() {
    Menu::displayHeader("Withdraw");

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
    if (amount < 0) cout << "Sorry, the withdraw amount can not be negative, please try again!\n";
    return;

    if (loggedInUser->withdraw(amount)) {
        cout << "Withdrawal successful! Your new balance is: " << loggedInUser->getBalance() << "\n";
        saveAllUsersToFile();
    }
    else {
        cout << "Insufficient balance.\n";
    }
}
void ATM::transfer() {
    Menu::displayHeader("Transfer");

    string receiverNumbers, pin;
    double amount;

    cout << "Enter recipient's phone numbers: ";
    cin >> receiverNumbers;
    cout << "Enter amount to transfer: ";
    cin >> amount;
    if (amount < 0) cout << "Sorry, the transfer amount can not be negative, please try again!\n";
    return;

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
                        saveAllUsersToFile();
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
    Menu::displayHeader("Check Balance");
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

void ATM::loadUsersFromFile() {
    ifstream inFile("D:\\ITCLASS\\OOP_BTL\\Updated OOP\\Updated OOP\\user.txt");
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    string phoneNumber, userName, password, pin;
    double balance;

    while (inFile >> phoneNumber >> balance) {
        inFile.ignore(); // Bỏ qua ký tự xuống dòng hoặc dấu cách sau balance
        getline(inFile, userName, '\t'); // Đọc đến ký tự tab hoặc newline nếu định dạng tách nhau bằng tab
        inFile >> password >> pin;

        UserAccount user(phoneNumber, balance, userName, phoneNumber, password, pin);
        users.push_back(user);
    }

    inFile.close();

    //cout << "Loaded users from file:\n";
    //int index = 1;
    //for (const auto& user : users) {
    //    cout << "User " << index++ << ":\n";
    //    cout << "  Phone: " << user.getPhoneNumber() << "\n"
    //        << "  Username: " << user.getUserName() << "\n"
    //        << "  Balance: " << user.getBalance() << "\n";
    //    cout << "-----------------------------------\n";
    //}
}


void ATM::saveUserToFile(const UserAccount& user) {
    ofstream outFile("D:\\ITCLASS\\OOP_BTL\\Updated OOP\\Updated OOP\\user.txt", ios::app);  // Mở tệp ở chế độ thêm
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    outFile << user.getPhoneNumber() << "\t"
        << user.getBalance() << "\t"
        << user.getUserName() << "\t"
        << user.getPassword() << "\t"
        << user.getTransactionPIN() << endl;

    outFile.close();
}
void ATM::saveAllUsersToFile() {
    ofstream outFile("D:\\ITCLASS\\OOP_BTL\\Updated OOP\\Updated OOP\\user.txt");
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    for (const UserAccount& user : users) {
        outFile << user.getPhoneNumber() << "\t"
            << user.getBalance() << "\t"
            << user.getUserName() << "\t"
            << user.getPassword() << "\t"
            << user.getTransactionPIN() << endl;
    }

    outFile.close();


}
