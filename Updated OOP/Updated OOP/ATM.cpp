﻿#include "ATM.h"
#include "Menu.h"
#include <iostream>

using namespace std;

ATM::ATM() : loggedInUser(nullptr) {
    // Tạo file `user.txt` nếu không tồn tại
    ofstream userFile("user.txt", ios::app);
    userFile.close(); // Đóng file sau khi mở

    // Tạo file `userHistory.txt` nếu không tồn tại
    ofstream historyFile("userHistory.txt", ios::app);
    historyFile.close(); // Đóng file sau khi mở
}

void ATM::run() {
    loadUsersFromFile();  // Load users from file at startup
    int choice;
    do {
        Menu::displayHeader("<<WELCOME TO W3O BANK>>");
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
            cout << ">> Choose an option: ";
            break;
        }
    } while (choice != 3);
}

void ATM::enterPassword(string& password)
{
    bool showPassword = false;
    char ch;

    cout << "Enter password (Press '/' to toggle visibility): ";

    while ((ch = _getch()) != 13) {  // Nhấn Enter để kết thúc nhập
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

            // Xóa dòng hiện tại để hiển thị lại mật khẩu với chế độ mới
            cout << string(100, '\r');  // Xóa dòng hiện tại
            cout << "Enter password (Press '/' to toggle visibility): "; //in ghi đè vào câu thông báo trước đó

            for (char p : password) { //in lại mật khẩu theo chế độ hiển thị đang chọn
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
}

void ATM::registerUser() {
    Menu::displayHeader("Register");
    string username, password, pin;
    string numbers = inputPhoneNumber();
    if (numbers == "N/A") return;
    cout << "Your phone number is valid\n" << endl;

    // Nhập tên người dùng và kiểm tra hợp lệ
    do {
        cout << "Enter the user name: ";
        getline(cin, username);

        if (!validateUserName(username)) {
            cout << "Invalid username! Your username should only contain letters and spaces.\n";
        }
    } while (!validateUserName(username));

    cout << endl;

    // Nhập mật khẩu với kiểm tra
    do {
        password.clear(); // Xóa mật khẩu để nhập lại nếu không hợp lệ
        enterPassword(password); // Gọi hàm nhập để nhập pass

        // Kiểm tra mật khẩu sau khi nhập xong
    } while (!validatePassword(password));

    cout << "Password is valid. Password entered successfully!\n";
    cout << endl; // Xuống dòng

    // Nhập mã PIN và kiểm tra hợp lệ
    do {
        cout << "Set your transaction PIN (6 digits): ";
        cin >> pin;

        if (!validatePin(pin)) {
            cout << "Invalid PIN! Your PIN must be exactly 6 digits and contain only numbers.\n";
        }
    } while (!validatePin(pin));

    cout << endl;

    // Tạo tài khoản mới và lưu thông tin
    UserAccount newUser(numbers, 0, username, numbers, password, pin);
    users.push_back(newUser);
    saveUserToFile(newUser);  // Lưu người dùng vào tệp

    cout << "User registered successfully!\n";
}


void ATM::login() {
    Menu::displayHeader("Login");

    string numbers, password;

    cout << "Enter your account's number: ";
    cin >> numbers;

    //Nhập mật khẩu tài khoản
    enterPassword(password);

    cout << endl; // Xuống dòng

    for (UserAccount& user : users) {
        if (user.getPhoneNumber() == numbers && user.getPassword(password)) {
            loggedInUser = &user;
            cout << "Login successful!\n";
            // Thêm dòng thông báo trước khi dừng lại hoàn thành thao tác log
            cout << "Press Enter to login...";
            cin.ignore();  // Bbỏ qua enter nếu có trước đó
            cin.get();     // Cho phép người dùng nhấn enter để hoàn thành
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
        case 1: deposit();
            cout << "Press Enter to return to menu...";
            cin.ignore();
            cin.get();
            break;
        case 2: withdraw();
            cout << "Press Enter to return to menu...";
            cin.ignore();
            cin.get();
            break;
        case 3: transfer();
            cout << "Press Enter to return to menu...";
            cin.ignore();
            cin.get();
            break;
        case 4: checkBalance();
            cout << "Press Enter to return to menu...";
            cin.ignore();
            cin.get();
            break;
        case 5: transactionHistory(); // Thêm tùy chọn này
            cout << "\nPress Enter to return to menu...";
            cin.ignore();
            cin.get();
            break;
        case 6: logout();
            break;
        default: cout << "Invalid choice, try again." << endl; break;
        }

    } while (choice != 6);
}


void ATM::logout() {
    Menu::displayHeader("Logout");

    if (loggedInUser == nullptr) {
        cout << "You are not logged in.\n";
        return;
    }

    char YN;
    cout << "Do you want to log out? (Y/N): ";
    cin >> YN;

    if (YN == 'Y' || YN == 'y') {
        loggedInUser = nullptr;
        cout << "Logged out successfully.\n";
    }
    else {
        system("cls");
        loginAfter();
    }
}

void ATM::deposit() {

    loggedInUser->syncBalanceFromHistory();

    Menu::displayHeader("Deposit");
    string transactionType = "Deposit";
    string pin;
    do {
        cout << "Enter your transaction PIN: ";
        cin >> pin;
        if (!loggedInUser->getTransactionPIN(pin)) {
            cout << "Incorrect PIN. Transaction failed, please try again!\n";
        }
    } while (!loggedInUser->getTransactionPIN(pin));

    double amount;
    do {
        cout << "Enter amount to deposit: ";
        cin >> amount;
    } while (!validateAmount(amount, transactionType)); //Dieu kien de lap lai viec nhap la khi nhap sai

    loggedInUser->deposit(amount);
    // Sử dụng fixed và setprecision để định dạng số
    cout << fixed << setprecision(2);
    cout << "\nDeposit successful! Your new balance is: " << loggedInUser->getBalance() << " VND\n";

    // Tạo giao dịch và thêm vào lịch sử
    Transaction txn;
    txn.dateTime = getCurrentDateTime();
    txn.type = "Deposit";
    txn.amount = amount;
    txn.balanceAfter = loggedInUser->getBalance();
    txn.details = "N/A";
    loggedInUser->addTransaction(txn);

    // Ghi giao dịch vào file lịch sử
    balanceFluctuation(*loggedInUser, txn);

    saveAllUsersToFile();
}

void ATM::withdraw() {
    // Đồng bộ số dư từ file trước khi rút tiền
    loggedInUser->syncBalanceFromHistory();

    Menu::displayHeader("Withdraw");
    string transactionType = "Withdraw";
    string pin;
    do {
        cout << "Enter your transaction PIN: ";
        cin >> pin;
        if (!loggedInUser->getTransactionPIN(pin)) {
            cout << "Incorrect PIN. Transaction failed, please try again!\n";
        }
    } while (!loggedInUser->getTransactionPIN(pin));

    double amount;
    do {
        cout << "Enter amount to withdraw: ";
        cin >> amount;
    } while (!validateAmount(amount, transactionType));

    if (loggedInUser->withdraw(amount)) {
        cout << fixed << setprecision(2); // Định dạng số tiền
        cout << "\nWithdrawal successful! Your new balance is: " << loggedInUser->getBalance() << " VND\n";

        // Tạo giao dịch và thêm vào lịch sử
        Transaction txn;
        txn.dateTime = getCurrentDateTime();
        txn.type = "Withdraw";
        txn.amount = amount;
        txn.balanceAfter = loggedInUser->getBalance();
        txn.details = "N/A";
        loggedInUser->addTransaction(txn);

        // Ghi giao dịch vào file lịch sử
        balanceFluctuation(*loggedInUser, txn);

        saveAllUsersToFile();
    }
    else {
        cout << "Insufficient balance.\n";
    }
}

void ATM::transfer() {

    loggedInUser->syncBalanceFromHistory();

    Menu::displayHeader("Transfer");
    string transactionType = "Transfer";
    string receiverNumbers, pin;
    double amount;

    cout << "\nEnter recipient's phone number: ";
    cin >> receiverNumbers;
    
    // Kiểm tra người nhận có tồn tại ngay sau khi nhập số điện thoại
    bool recipientFound = false;
    UserAccount* recipient = nullptr;
    for (UserAccount& user : users) {
        if (user.getPhoneNumber() == receiverNumbers) {
            recipientFound = true;
            recipient = &user;
            break;
        }
    }

    if (!recipientFound) {
        cout << "Recipient not found.\n";
        char retryChoice;
        cout << "Do you want to try again? (Y/N): ";
        cin >> retryChoice;

        if (retryChoice == 'Y' || retryChoice == 'y') {
            transfer();  // Gọi lại hàm transfer để thực hiện lại từ đầu
        }
        else {
            cout << "Transaction cancelled.\n";
        }
        return;
    }

    do {
        cout << "Enter amount to transfer: ";
        cin >> amount;
    } while (!validateAmount(amount, transactionType));

    do {
        cout << "Enter your transaction PIN: ";
        cin >> pin;

        if (!loggedInUser->getTransactionPIN(pin)) {
            cout << "Incorrect PIN. Transaction failed, please try again!\n";
        }
    } while (!loggedInUser->getTransactionPIN(pin));

    // Kiểm tra nhập OTP được gửi về máy
    int otp = generateOTP(); // Tạo mã OTP
    cout << "An OTP has been sent to your registered device: " << setw(6) << setfill('0') << otp << endl; // Đảm bảo mã OTP luôn có 6 chữ số
    int userInput;
    do {
        cout << "Enter OTP code to confirm money transfer: ";
        cin >> userInput;
        if (userInput == otp) {
            // Kiểm tra nếu người gửi có đủ tiền để chuyển
            if (loggedInUser->withdraw(amount)) {
                recipient->deposit(amount);
                cout << "\033[1;35m";
                cout << "\n|=======================================================================================================================================|" << "\n";
                cout << fixed << setprecision(2) << "\033[1;37m" << "                                      Transfer to " << recipient->getUserName() << " successful! -" << amount << " VND\n";
                cout << "\033[1;35m";
                cout << "|---------------------------------------------------------------------------------------------------------------------------------------|" << "\n";
                cout << "                                               >>[Receiver]:      " << "\033[1;37m" << recipient->getPhoneNumber() << "\n";
                cout << "\033[1;35m";
                cout << "|---------------------------------------------------------------------------------------------------------------------------------------|" << "\n";
                cout << "                                               >>[Recipient Name]:      " << "\033[1;37m" << recipient->getUserName() << "\n";
                cout << "\033[1;35m";
                cout << "|---------------------------------------------------------------------------------------------------------------------------------------|" << "\n";
                cout << fixed << setprecision(2) << "                                               >>[Amount]:       " << "\033[1;37m" << "+" << amount << " VND\n";
                cout << "\033[1;35m";
                cout << "|=======================================================================================================================================|" << "\n\n";
                cout << "\033[0m";

                // Tạo giao dịch gửi tiền
                Transaction txnSent;
                txnSent.dateTime = getCurrentDateTime();
                txnSent.type = "Transfer Sent";
                txnSent.amount = amount;
                txnSent.balanceAfter = loggedInUser->getBalance();
                txnSent.details = "To: " + recipient->getPhoneNumber() + " (" + shortenName(recipient->getUserName()) + ")";
                loggedInUser->addTransaction(txnSent);

                // Ghi giao dịch gửi tiền vào file lịch sử
                balanceFluctuation(*loggedInUser, txnSent);

                // Tạo giao dịch nhận tiền cho người nhận
                Transaction txnReceived;
                txnReceived.dateTime = getCurrentDateTime();
                txnReceived.type = "Transfer Received";
                txnReceived.amount = amount;
                txnReceived.balanceAfter = recipient->getBalance();
                txnReceived.details = "From: " + loggedInUser->getPhoneNumber() + " (" + shortenName(loggedInUser->getUserName()) + ")";
                recipient->addTransaction(txnReceived);

                // Ghi giao dịch nhận tiền vào file lịch sử
                balanceFluctuation(*recipient, txnReceived);

                saveAllUsersToFile();
            }
            else {
                cout << "Insufficient balance.\n";
            }
            return;
        }
        if (userInput != otp) {
            cout << "Incorrect OTP code, please try again..." << endl;
        }
    } while (userInput != otp);
    cout.unsetf(ios::fixed);//reset định dạng cout
}


void ATM::transactionHistory() {
    if (loggedInUser == nullptr) {
        cout << "You need to log in first to view the transaction history.\n";
        return;
    }

    ifstream inFile("userHistory.txt");
    if (!inFile) {
        cout << "Error opening userHistory.txt!" << endl;
        return;
    }

    string line;
    bool hasTransaction = false;

    Menu::displayHeader("Transaction History");

    cout << "\033[1;37m\n";
    cout << "+=======================================================================================================================================+\n";
    cout << "|---------------------------------------------------------------------------------------------------------------------------------------|\n";
    cout << "| Date & Time\t\tType\t\t\tAmount\t\t\tBalance After\t\tDetails                                 |\n";
    cout << "|---------------------------------------------------------------------------------------------------------------------------------------|";

    int y = 10;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string phoneNumber, userName, dateTime, type, details;
        double amount, balanceAfter;

        // Tách các trường bằng istringstream
        getline(iss, phoneNumber, '\t');
        getline(iss, userName, '\t');
        getline(iss, dateTime, '\t');
        getline(iss, type, '\t');
        iss >> amount >> balanceAfter;
        iss.ignore(); // Bỏ qua tab hoặc khoảng trắng sau balanceAfter
        getline(iss, details); // Lấy phần còn lại của dòng làm chi tiết

        // Kiểm tra nếu số điện thoại trùng với người dùng hiện tại
        if (phoneNumber == loggedInUser->getPhoneNumber()) {
            hasTransaction = true;
            gotoxy(0, y);
            cout << "|";
            gotoxy(2, y); // X đặt một vị trí phù hợp để căn chỉnh
            cout << dateTime;
            gotoxy(24, y); // Thay đổi X để đặt vị trí cho 'Type'
            cout << type;
            gotoxy(48, y); // Thay đổi X để đặt vị trí cho 'Amount'
            // Định dạng số liệu (giữ 2 chữ số thập phân)
            cout << fixed << setprecision(2) << amount;
            gotoxy(72, y); // Thay đổi X để đặt vị trí cho 'Balance After'
            cout << fixed << setprecision(2) << balanceAfter;
            gotoxy(96, y); // Thay đổi X để đặt vị trí cho 'Details'
            cout << details;
            gotoxy(136, y);
            cout << "|" << endl;
            cout << "|---------------------------------------------------------------------------------------------------------------------------------------|\n";

            y = y + 2; // Di chuyển xuống hàng tiếp theo */
        }
    }
    int y2 = 11;
    if (!hasTransaction) {
        gotoxy(0, y2);
        cout << "|";
        gotoxy(2, y2); // X đặt một vị trí phù hợp để căn chỉnh
        cout << "No transactions found for your account";
        gotoxy(136, y2);
        cout << "|" << endl;
        cout << "|---------------------------------------------------------------------------------------------------------------------------------------|\n";
    }


    cout << "+=======================================================================================================================================+\n";
    cout << "\033[0m";
    cout.unsetf(ios::fixed);
    inFile.close();
}

void ATM::checkBalance() {
    Menu::displayHeader("Check Balance");
    cout << "\033[1;35m";
    cout << "\n|=======================================================================================================================================|" << "\n";
    cout << "                                        >>[Account]:         " << "\033[1;37m" << loggedInUser->getPhoneNumber() << "\n";
    cout << "\033[1;35m";
    cout << "|---------------------------------------------------------------------------------------------------------------------------------------|" << "\n";
    cout << "                                        >>[User Name]:         " << "\033[1;37m" << loggedInUser->getUserName() << "\n";
    cout << "\033[1;35m";
    cout << "|---------------------------------------------------------------------------------------------------------------------------------------|" << "\n";
    cout << fixed << setprecision(2) << "                                        >>[Your balance is]:         " << "\033[1;37m" << loggedInUser->getBalance() << "VND\n";
    cout << "\033[1;35m";
    cout << "|=======================================================================================================================================|" << "\n\n";
    cout << "\033[0m";
    cout.unsetf(ios::fixed);
}

string ATM::getCurrentDateTime() {
    time_t now = time(0); // Lấy thời gian hiện tại
    tm ltm;
    localtime_s(&ltm, &now); // Sử dụng localtime_s thay vì localtime

    stringstream ss;
    ss << setw(2) << setfill('0') << ltm.tm_mday << "/"
        << setw(2) << setfill('0') << (ltm.tm_mon + 1) << "/"
        << setw(2) << setfill('0') << (ltm.tm_year % 100) << " "
        << setw(2) << setfill('0') << ltm.tm_hour << ":"
        << setw(2) << setfill('0') << ltm.tm_min << ":"
        << setw(2) << setfill('0') << ltm.tm_sec;

    return ss.str();
}

void ATM::balanceFluctuation(const UserAccount& user, const Transaction& txn) {
    ofstream outFile("userHistory.txt", ios::app); // Mở file ở chế độ ghi thêm
    if (!outFile) {
        cout << "Error opening userHistory.txt for writing!" << endl;
        return;
    }

    // Chuyển đổi số tiền và số dư sau giao dịch sang chuỗi với định dạng cố định 2 chữ số thập phân
    ostringstream amountStream, balanceStream;
    amountStream << fixed << setprecision(2) << txn.amount;
    balanceStream << fixed << setprecision(2) << txn.balanceAfter;

    string amountStr = amountStream.str();
    string balanceStr = balanceStream.str();

    // Ghi thông tin giao dịch với định dạng: Số điện thoại, Tên người dùng, Thời gian, Loại giao dịch, Số tiền, Số dư sau giao dịch, Chi tiết
    outFile << user.getPhoneNumber() << "\t"
        << user.getUserName() << "\t"
        << txn.dateTime << "\t"
        << txn.type << "\t"
        << amountStr << "\t"
        << balanceStr << "\t"
        << txn.details << "\n";

    outFile.close();
}

// Hàm kiểm tra xem số điện thoại đã được đăng ký hay chưa
bool ATM::isPhoneNumberRegistered(const string& phone) {
    for (const UserAccount& user : users) {
        if (user.getPhoneNumber() == phone) {
            return true; // Số điện thoại đã được đăng ký
        }
    }
    return false; // Số điện thoại chưa được đăng ký
}


string ATM::inputPhoneNumber() {
    string phone;
    cin.ignore();
    bool firstAttempt = true; // Biến để theo dõi nếu là lần nhập đầu tiên
    do {
        if (!firstAttempt) {
            cout << "Invalid phone number format, please try again." << endl;
        }
        cout << "Enter your phone number: ";
        getline(cin, phone);
        firstAttempt = false; // Sau lần nhập đầu tiên

        // Kiểm tra xem số điện thoại đã được đăng ký chưa
        if (isPhoneNumberRegistered(phone)) {
            cout << "This phone number has already been registered. Please try a different one." << endl;
            cout << "Do you want to login or continue register? (Y/N): ";
            char YN;
            cin >> YN;
            if (YN == 'Y' || YN == 'y') return "N/A";
            firstAttempt = true; // Để tiếp tục yêu cầu nhập lại
            cin.ignore();
        }
    } while (!validatePhoneNumber(phone) || isPhoneNumberRegistered(phone));

    return phone;
}

bool ATM::validatePhoneNumber(const string& phone) {
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
bool ATM::validateUserName(const string& username) {
    for (char c : username) {
        if (!isalpha(c) && c != ' ') { // Chỉ cho phép chữ cái và khoảng trắng
            return false;
        }
    }
    return true;
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
        cout << "Password must contain at least 1 uppercase character, number and special character. Please try again!\n";
        return false;
    }

    return true;
}
bool ATM::validatePin(const string& pin) {
    if (pin.size() != 6) return false; // Kiểm tra độ dài
    for (char c : pin) {
        if (!isdigit(c)) { // Kiểm tra từng ký tự có phải số hay không
            return false;
        }
    }
    return true;
}

bool ATM::validateAmount(double amount, const string& transactionType) {
    if (amount <= 0 || static_cast<int>(amount) % 5 != 0) { // amount được chuyển sang kiểu int bằng cách sử dụng static_cast<int>(amount)
        cout << "The amount must be positive and a multiple of 5, please try again!" << endl;
        return false;
    }
    if (transactionType == "Deposit" || transactionType == "Withdraw") {
        if (amount < 50000.0) {
            cout << "The minimum amount for performing the function is 50000VND, please try again!" << endl;
            return false;
        }
    }
    if (transactionType == "Transfer") {
        if (amount < 10000.0) {
            cout << "The minimum amount for performing the function is 10000VND, please try again!" << endl;
            return false;
        }
    }
    return true;
}

int ATM::generateOTP() {
    srand(static_cast<unsigned int>(time(0))); // Khởi tạo số ngẫu nhiên gồm 6 chữ số
    return rand() % 900000 + 100000;
}

void ATM::loadUsersFromFile() {
    ifstream inFile("user.txt");
    if (!inFile) {
        cout << "Error opening user.txt!" << endl;
        return;
    }

    string phoneNumber, userName, password, pin;
    double balance;

    while (getline(inFile, phoneNumber, '\t') && inFile >> balance) {
        inFile.ignore(); // Bỏ qua ký tự xuống dòng hoặc dấu cách sau balance
        getline(inFile, userName, '\t');
        getline(inFile, password, '\t');
        getline(inFile, pin);

        UserAccount user(phoneNumber, balance, userName, phoneNumber, password, pin);
        users.push_back(user);
    }

    inFile.close();
}

void ATM::saveUserToFile(const UserAccount& user) {
    ofstream outFile("user.txt", ios::app);  // Mở tệp ở chế độ thêm
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
    ofstream outFile("user.txt");
    if (!outFile) {
        cout << "Error opening user.txt for writing!" << endl;
        return;
    }

    for (const UserAccount& user : users) {
        outFile << user.getPhoneNumber() << "\t"
            << user.getBalance() << "\t"
            << user.getUserName() << "\t"
            << user.getPassword() << "\t"
            << user.getTransactionPIN() << "\n";
    }

    outFile.close();
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
string shortenName(const string& fullName) {
    stringstream ss(fullName);
    string word, shortenedName;

    vector<string> words; // Lưu tất cả các từ trong tên
    while (ss >> word) {
        words.push_back(word);
    }

    if (words.empty()) return fullName; // Trả về tên ban đầu nếu không có từ nào

    for (size_t i = 0; i < words.size() - 1; ++i) {
        shortenedName += toupper(words[i][0]); // Viết hoa ký tự đầu của từng từ
        shortenedName += ".";
    }

    // Thêm từ cuối cùng vào đầy đủ
    shortenedName += words.back();
    return shortenedName;
}